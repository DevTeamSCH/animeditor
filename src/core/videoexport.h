#ifndef VIDEOEXPORT_H
#define VIDEOEXPORT_H

#include "animationmodel.h"
#include "core_global.h"

namespace SchMatrix {
namespace FFmpeg {

void CORESHARED_EXPORT videoExport(SchMatrix::AnimationModel *animModel,
                                   QGraphicsScene *scene,
                                   QString videoExportPath);
}  // namespace FFmpeg
}  // namespace SchMatrix

#endif  // VIDEOEXPORT_H
