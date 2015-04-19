#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <string>
#include <memory>

#include <iosfwd>

#include <osg/Texture2D>

#include <boost/shared_ptr.hpp>

namespace osg
{
    class Texture2D;
}

namespace Video
{

    struct VideoState;
    class MovieAudioFactory;

    /**
     * @brief Plays a video on an Ogre texture.
     */
    class VideoPlayer
    {
    public:
        VideoPlayer();
        ~VideoPlayer();

        /// @brief Set the MovieAudioFactory to use.
        /// @par This class must be implemented by the user and is responsible for reading the decoded audio data.
        /// @note If you do not set up a MovieAudioFactory, then audio streams will be ignored and the video will be played with no sound.
        /// @note Takes ownership of the passed pointer.
        void setAudioFactory (MovieAudioFactory* factory);

        /// Return true if a video is currently playing and it has an audio stream.
        bool hasAudioStream();

        /// Play the given video. If a video is already playing, the old video is closed first.
        /// @note The video will be unpaused by default. Use the pause() and play() methods to control pausing.
        void playVideo (boost::shared_ptr<std::istream> inputstream);

        /// Get the current playback time position in the video, in seconds
        double getCurrentTime();

        /// Get the duration of the video in seconds
        double getDuration();

        /// Seek to the specified time position in the video
        void seek(double time);

        void play();
        void pause();
        bool isPaused();

        /// This should be called every frame by the user to update the video texture.
        /// @return Returns true if the video is still playing, false if we have reached the end of the video stream.
        bool update();

        /// Stop the currently playing video, if a video is playing.
        void close();

        /// Return the texture of the currently playing video, or a null pointer if no video is playing.
        osg::ref_ptr<osg::Texture2D> getVideoTexture();

        /// Return the width of the currently playing video, or 0 if no video is playing.
        int getVideoWidth();
        /// Return the height of the currently playing video, or 0 if no video is playing.
        int getVideoHeight();


    private:
        VideoState* mState;

        std::auto_ptr<MovieAudioFactory> mAudioFactory;
    };

}

#endif
