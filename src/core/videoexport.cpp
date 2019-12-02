#include "videoexport.h"

#include <QDebug>
#include <QImage>
#include <QPainter>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libswscale/swscale.h>
}

static inline char* error(int errnum) {
  char buff[AV_ERROR_MAX_STRING_SIZE] = {0};
  return av_make_error_string(buff, AV_ERROR_MAX_STRING_SIZE, errnum);
}

static void encode(AVCodecContext* enc_ctx, AVFrame* frame, AVPacket* pkt,
                   AVStream* stream, AVFormatContext* format) {
  if (avcodec_send_frame(enc_ctx, frame) < 0) {
    qCritical() << "Error sending the frame to the encoder";
    exit(1);
  }

  // read all the available output packets (in general there may be any number
  // of them
  int ret = 0;
  while (ret >= 0) {
    ret = avcodec_receive_packet(enc_ctx, pkt);
    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
      return;
    else if (ret < 0) {
      qCritical() << "Error encoding video frame";
      exit(1);
    }

    av_packet_rescale_ts(pkt, enc_ctx->time_base, stream->time_base);
    pkt->stream_index = stream->index;

    int err = av_interleaved_write_frame(format, pkt);
    if (err < 0) {
      qCritical() << "Error while writing audio frame:" << error(err);
      exit(1);
    }

    av_packet_unref(pkt);
  }
}

namespace SchMatrix {
namespace FFmpeg {

void videoExport(SchMatrix::AnimationModel* animModel, QGraphicsScene* scene,
                 QString videoExportPath) {
  int ret = 0;
  auto sceneSize = scene->sceneRect().toRect().size();

  std::string videoPath = videoExportPath.toStdString();
  const char* videoFilename = videoPath.c_str();

  // Format context
  AVFormatContext* outputFormatContext;
  if (avformat_alloc_output_context2(&outputFormatContext, nullptr, "mp4",
                                     videoFilename) < 0) {
    qCritical() << "Could not create output context";
    exit(1);
  }

  // Metadata
  av_dict_set(&outputFormatContext->metadata, "title", "Test", 0);
  av_dict_set(&outputFormatContext->metadata, "author", "Matrix", 0);
  av_dict_set(&outputFormatContext->metadata, "date", "2019", 0);
  av_dict_set(&outputFormatContext->metadata, "comment",
              "Made with AnimEditor using FFmpeg", 0);

  // Video
  AVFrame* videoFrame = av_frame_alloc();
  AVCodec* videoCodec =
      avcodec_find_encoder(outputFormatContext->oformat->video_codec);
  AVCodecContext* videoCodecContext = avcodec_alloc_context3(videoCodec);
  AVStream* videoStream = avformat_new_stream(outputFormatContext, nullptr);
  AVPacket* videoPacket = av_packet_alloc();

  // Video context
  videoCodecContext->width = sceneSize.width();
  videoCodecContext->height = sceneSize.height();
  AVRational time_base = {1, 30};
  videoCodecContext->time_base = time_base;
  videoStream->time_base = time_base;
  videoCodecContext->pix_fmt = AV_PIX_FMT_YUV444P;

  // Video frame
  videoFrame->format = videoCodecContext->pix_fmt;
  videoFrame->width = videoCodecContext->width;
  videoFrame->height = videoCodecContext->height;

  if (av_frame_get_buffer(videoFrame, 0) < 0) {
    qCritical() << "Could not allocate the video frame data";
    exit(1);
  }

  if (avcodec_parameters_from_context(videoStream->codecpar,
                                      videoCodecContext) < 0) {
    qCritical() << "Could not copy the stream parameters";
    exit(1);
  }

  // h264 specific options
  av_opt_set(videoCodecContext->priv_data, "crf", "17", 0);
  av_opt_set(videoCodecContext->priv_data, "preset", "veryslow", 0);
  av_opt_set(videoCodecContext->priv_data, "profile", "high444", 0);

  ret = avcodec_open2(videoCodecContext, videoCodec, nullptr);
  if (ret < 0) {
    qCritical() << "Could not open video codec:" << error(ret);
    exit(1);
  }

  // SwsContext
  SwsContext* swsContext = sws_getContext(
      videoCodecContext->width, videoCodecContext->height, AV_PIX_FMT_RGB24,
      videoCodecContext->width, videoCodecContext->height,
      videoCodecContext->pix_fmt, 0, nullptr, nullptr, nullptr);

  // Audio
  // TODO

  // Open the output file
  ret = avio_open(&outputFormatContext->pb, videoFilename, AVIO_FLAG_WRITE);
  if (ret < 0) {
    qCritical() << "Could not open" << videoFilename << ":" << error(ret);
    exit(1);
  }

  //  Write the stream header
  ret = avformat_write_header(outputFormatContext, nullptr);
  if (ret < 0) {
    qCritical() << "Error occurred when opening output file:" << error(ret);
    exit(1);
  }

  // Encoding
  // Encode Video
  QImage image(sceneSize, QImage::Format_RGB888);
  QPainter painter(&image);
  const uint8_t* const inData[1] = {image.constBits()};
  const int inLinesize[1] = {image.bytesPerLine()};

  for (int i = 0; i < animModel->lastFrame() + 1; ++i) {
    if (av_frame_make_writable(videoFrame) < 0) exit(1);

    animModel->setFrame(i);
    image.fill(0);
    scene->render(&painter);

    // Color conversion
    sws_scale(swsContext, inData, inLinesize, 0, videoCodecContext->height,
              videoFrame->data, videoFrame->linesize);

    videoFrame->pts = i;

    encode(videoCodecContext, videoFrame, videoPacket, videoStream,
           outputFormatContext);
  }

  // Flush the encoder
  encode(videoCodecContext, nullptr, videoPacket, videoStream,
         outputFormatContext);

  //  Write the trailer
  av_write_trailer(outputFormatContext);

  // Free data structures
  av_frame_free(&videoFrame);
  av_packet_free(&videoPacket);
  avcodec_free_context(&videoCodecContext);
  sws_freeContext(swsContext);

  // Close the output file
  avio_closep(&outputFormatContext->pb);
  avformat_free_context(outputFormatContext);
}

}  // namespace FFmpeg
}  // namespace SchMatrix
