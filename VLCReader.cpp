#include "vlcreader.h"
#include <cstdlib>
#include <iostream>

VLCReader::VLCReader(char*url)
    : inst(0),mp(0), pixel(0), w(0), h(0), rtspAddress(url)
{
    const char * const vlc_args[] = {
        "-I", "dummy",      // Don't use any interface
        "--ignore-config",  // Don't use VLC's config
        "--no-audio",       // skip any audio track
        "--verbose=1",      // change verbosity for debugging purpose
    };

    inst = libvlc_new(sizeof(vlc_args) / sizeof(vlc_args[0]), vlc_args);
    mp = libvlc_media_player_new(inst);
	
    libvlc_video_set_callbacks(mp, &cb_lock, &cb_unlock, &cb_display, this);
}

VLCReader::~VLCReader()
{
    libvlc_media_player_stop(mp);
    libvlc_media_player_release(mp);
    libvlc_release(inst);
}

void VLCReader::start(int wantW, int wantH)
{
    libvlc_media_player_pause(mp);
    libvlc_media_t *media = libvlc_media_new_location(inst, rtspAddress);
    libvlc_media_player_set_media(mp, media);
	//libvlc_media_add_option(media, ":network-caching=300");
    libvlc_media_release(media);

    libvlc_video_set_format(mp, "RV24", wantW, wantH, wantW*3);
	//libvlc_video_set_format(mp, "RV32", wantW, wantH, wantW*4);
	//libvlc_video_set_format(mp, "RGBA", wantW, wantH, wantW*4);

    libvlc_media_player_play(mp);
}

void VLCReader::pause(bool paused)
{
    if(mp){
        libvlc_media_player_set_pause(mp, paused);
    }
}

unsigned char * VLCReader::updataSize()
{
    int w = libvlc_video_get_width(mp);
    int h = libvlc_video_get_height(mp);
    if (!w || !h)
        return 0;
    if (pixel && (this->w != w || this->h != h)){
        delete[] pixel;
        pixel = 0;
    }
    if (!pixel){
        pixel = new unsigned char[w*h*3];
        this->w = w;
        this->h = h;
    }
    return pixel;
}

void* VLCReader::cb_lock(void *opaque, void **plane)
{
    VLCReader *p = (VLCReader*) opaque;
    *plane = p->updataSize();
    return *plane;
}
void VLCReader::cb_unlock(void *opaque, void *picture, void * const *plane)
{
    VLCReader *p = (VLCReader*) opaque;
    unsigned char *pix = (unsigned char*)picture;

    if (pix){
        p->img = cv::Mat(p->h, p->w, CV_8UC3, pix);

		/*vimg.cols       = this->width;
		vimg.rows       = this->height;
		vimg.channels   = _IMG_CHANNELS;

		for (int y = 0; y < this->height; y++) {
        auto row = vector<Vpixel>{};

			for (int x = 0; x < this->width; x++) {
				auto point = &raw[y * this->width * _RAW_CHANNELS + x * _RAW_CHANNELS];
				auto alpha = (float) point[3] / 255.0; 

				row.push_back(Vpixel{
					(float) _BG_COLOR * (1 - alpha) + (float) point[0] * alpha,
					(float) _BG_COLOR * (1 - alpha) + (float) point[1] * alpha,
					(float) _BG_COLOR * (1 - alpha) + (float) point[2] * alpha
				});
			}
		}
        vimg.data.push_back(row);
    
		p->img = cv::Mat::zeros(p->h, p->w, CV_8UC3);

		for (int y = 0; y < p->w; y++) {
			for (int x = 0; x < p->h; x++) {
				p->img.at<cv::Vec3b>(x, y)[0] = src.data[x][y].b;
				p->img.at<cv::Vec3b>(x, y)[1] = src.data[x][y].g;
				p->img.at<cv::Vec3b>(x, y)[2] = src.data[x][y].r;
			}
		}
*/

    }
}
void VLCReader::cb_display(void *opaque, void *picture)
{
}