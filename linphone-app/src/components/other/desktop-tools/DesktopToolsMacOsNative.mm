#include "DesktopToolsMacOs.hpp"
#import <AVFoundation/AVFoundation.h>
#import <ScreenCaptureKit/ScreenCaptureKit.h>
#include <QDebug>
#include <QThread>
#include "components/videoSource/VideoSourceDescriptorModel.hpp"

void DesktopTools::init(){
// Request permissions
  if([AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo] != AVAuthorizationStatusAuthorized) {
    qDebug() << "Requesting Video permission";
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL) {}];
  }
  if([AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio] != AVAuthorizationStatusAuthorized){
    qDebug() << "Requesting Audio permission";
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL) {}];
  }
}


void *DesktopTools::getDisplay(int screenIndex){
    __block CGDirectDisplayID display = 0;
    __block BOOL sync = FALSE;
    [SCShareableContent getShareableContentWithCompletionHandler:^(SCShareableContent *shareableContent, NSError *error){
      if(!error || error.code == 0){
        display = shareableContent.displays[screenIndex].displayID;
      }else
        qWarning() << "Error while getting shareable context" << error.code <<  [[error localizedDescription] UTF8String] <<  [[error localizedFailureReason] UTF8String];
      sync = TRUE;
    }];
  while(!sync)
    QThread::msleep(2);
  return reinterpret_cast<void*>(display);
}

int DesktopTools::getDisplayIndex(void* screenSharing){
    __block int index = 0;
    __block BOOL sync = FALSE;
    CGDirectDisplayID displayId = *(CGDirectDisplayID*)&screenSharing;
    [SCShareableContent getShareableContentWithCompletionHandler:^(SCShareableContent *shareableContent, NSError *error){
      if(!error || error.code == 0){
        for(int i = 0 ; i < shareableContent.displays.count ; ++i) {
          if(displayId == shareableContent.displays[i].displayID) {
            index = i;
            break;
          }
        }
      }else
        qWarning() << "Error while getting shareable context" << error.code <<  [[error localizedDescription] UTF8String] <<  [[error localizedFailureReason] UTF8String];
      sync = TRUE;
    }];
  while(!sync)
    QThread::msleep(2);
  return index;
}

void DesktopTools::getWindowIdFromMouse(VideoSourceDescriptorModel *model) {
      __block id globalMonitorId;
      __block id localMonitorId;
      __block DesktopTools * tools = this;
      emit windowIdSelectionStarted();
      globalMonitorId = [NSEvent addGlobalMonitorForEventsMatchingMask:NSEventMaskLeftMouseDown | NSEventMaskRightMouseDown
                                    handler:^(NSEvent *event){
              CGWindowID windowID = (CGWindowID)[event windowNumber];

                __block BOOL ok = FALSE;
                [SCShareableContent getShareableContentWithCompletionHandler:^(SCShareableContent *shareableContent, NSError *error){
                    if(!error || error.code == 0){
                        for(int i = 0 ; i < shareableContent.windows.count ; ++i)
                            if( shareableContent.windows[i].windowID == windowID) {
                                qDebug() << "Found!";
                            }else
                              qWarning() << i << " -> " << shareableContent.windows[i].windowID;
                    }/*else
                        qWarning() << "Error while getting shareable context" << error.code <<  [[error localizedDescription] UTF8String] <<  [[error localizedFailureReason] UTF8String];
*/
                    ok = TRUE;
                }];

                while(!ok) std::this_thread::sleep_for(std::chrono::microseconds(100));
                if(event.type == NSEventTypeLeftMouseDown)
                  model->setScreenSharingWindow(reinterpret_cast<void *>(windowID));
              [NSEvent removeMonitor:globalMonitorId];
              [NSEvent removeMonitor:localMonitorId];
              emit tools->windowIdSelectionEnded();
  }];
      localMonitorId = [NSEvent addLocalMonitorForEventsMatchingMask:NSEventMaskLeftMouseDown | NSEventMaskRightMouseDown
                                    handler:^NSEvent *(NSEvent *event){
              CGWindowID windowID = (CGWindowID)[event windowNumber];
              if(event.type == NSEventTypeLeftMouseDown)
                model->setScreenSharingWindow(reinterpret_cast<void *>(windowID));
              [NSEvent removeMonitor:globalMonitorId];
              [NSEvent removeMonitor:localMonitorId];
              emit tools->windowIdSelectionEnded();
              return nil;
  }];
}
