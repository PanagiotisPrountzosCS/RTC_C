
#include "graphics/canvas.h"

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "extras/algorithms.h"
#include "extras/globaldefs.h"

Canvas canvas(size_t width, size_t height) {
    Color* pixels = (Color*)malloc(width * height * sizeof(Color));
    for (int i = 0; i < width * height; i++) {
        pixels[i] = (Color){0, 0, 0};
    }
    return (Canvas){width, height, pixels};
}

void canvas_destroy(Canvas* c) {
    assert(c);
    free(c->pixels);
}

void canvas_to_ppm(const Canvas* c, const char* filename) {
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return;
    }

    char header[100];
    sprintf(header, "P3\n%d %d\n255\n", c->width, c->height);

    int bytes_written = write(fd, header, strlen(header));

    if (bytes_written == -1) {
        perror("write");
        close(fd);
        return;
    }

    // ppm wants 70 chars per line
    char buffer[RTCC_MAX_LINE_LENGTH_PPM] = "";
    for (int i = 0; i < c->height; i++) {
        size_t current_line_size = 0;
        for (int j = 0; j < c->width; j++) {
            Color pixel = canvas_pixel_at(c, j, i);
            int red = clamp(pixel.r * 255, 0, 255);
            int green = clamp(pixel.g * 255, 0, 255);
            int blue = clamp(pixel.b * 255, 0, 255);

            int red_len = int_len(red);
            int green_len = int_len(green);
            int blue_len = int_len(blue);

            if (current_line_size + red_len < RTCC_MAX_LINE_LENGTH_PPM) {
                current_line_size +=
                    sprintf(buffer + current_line_size, "%d ", red);
            } else {
                buffer[current_line_size - 1] = '\n';
                write(fd, buffer, current_line_size);
                current_line_size = sprintf(buffer, "%d ", red);
            }
            if (current_line_size + green_len < RTCC_MAX_LINE_LENGTH_PPM) {
                current_line_size +=
                    sprintf(buffer + current_line_size, "%d ", green);
            } else {
                buffer[current_line_size - 1] = '\n';
                write(fd, buffer, current_line_size);
                current_line_size = sprintf(buffer, "%d ", green);
            }
            if (current_line_size + blue_len < RTCC_MAX_LINE_LENGTH_PPM) {
                current_line_size +=
                    sprintf(buffer + current_line_size, "%d ", blue);
            } else {
                buffer[current_line_size - 1] = '\n';
                write(fd, buffer, current_line_size);
                current_line_size = sprintf(buffer, "%d ", blue);
            }
        }
        buffer[current_line_size - 1] = '\n';
        write(fd, buffer, current_line_size);
        current_line_size = 0;
    }

    close(fd);
}