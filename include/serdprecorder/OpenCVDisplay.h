#pragma once

#include <memory>

#include <opencv2/core.hpp>

#include "active_object/active.h"
#include "liboculus/SimplePingResult.h"

namespace serdprecorder {

  using std::vector;
  class SerdpRecorder;

  class OpenCVDisplay {
  public:


    OpenCVDisplay( bool enabled = true );
    OpenCVDisplay( const std::shared_ptr<SerdpRecorder> &parent, bool enabled = true );

    bool setEnabled( bool e ) { return _enabled = e; }

    void showVideo( vector< cv::Mat > mats )
    { if( _enabled) _thread->send( std::bind(&OpenCVDisplay::implShowVideo, this, mats) ); }

    void showSonar( const std::shared_ptr<liboculus::SimplePingResult> &ping )
    { if( _enabled) _thread->send( std::bind(&OpenCVDisplay::implShowSonar, this, ping) ); }

    float setPreviewScale( float scale )
    { _previewScale = scale;
      return _previewScale; }


  protected:

    void implShowVideo( vector< cv::Mat > mats );
    void resizeImage( const cv::Mat &rawImage, cv::Mat &scaledImage );

    void implShowSonar( const std::shared_ptr<liboculus::SimplePingResult> &ping );

  private:

    bool _enabled;
    float _previewScale;
    std::shared_ptr<SerdpRecorder> _parent;

    std::unique_ptr<active_object::Active> _thread;

  };


}
