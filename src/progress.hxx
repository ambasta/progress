//
// Created by amitprakash on 12/8/16.
//

#ifndef PROGRESS_PROGRESS_HXX
#define PROGRESS_PROGRESS_HXX

#include <iostream>
#include <string>
#include <sys/ioctl.h>

namespace Ambasta {
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

    class ProgressBar {
    private:
        unsigned int total;
        unsigned int progress;
        unsigned int colwidth;
        std::string message;
    public:
        ProgressBar(unsigned int total_, std::string message_) : total(total_), progress(0), message(message_) {
            struct winsize w;
            ioctl(0, TIOCGWINSZ, &w);
            colwidth = w.ws_col;
            show();
        }

        ~ProgressBar() {
            progress = total;
            show();
            std::cout << std::endl << std::flush;
        }

        void update(unsigned int progress_) {
            progress = progress_;
            show();
        }

        void show() {
            std::string prefix = message
                                 + std::string{" "} + std::to_string(progress)
                                 + std::string{"/"} + std::to_string(total);

            // 4 Additional spaces for space, braces and carriage return in " [...]\r"
            int prefix_length = prefix.length() + 4;
            int progress_length = colwidth - prefix_length;
            int completed = progress * progress_length / total;
            int remaining = progress_length - completed;

            std::string hashes = std::string(completed, '#');
            std::string period = std::string(progress_length - completed, '.');

            std::cout
                    << RED << message << " "
                    << GREEN << progress
                    << RESET << "/"
                    << BLUE << total
                    << GREEN << " [" << hashes
                    << BLUE << period
                    << GREEN << "]\r"
                    << RESET << std::flush;
        }
    };
}
#endif //PROGRESS_PROGRESS_HXX
