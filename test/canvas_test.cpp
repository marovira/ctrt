#include "canvas.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Canvas] - static canvas")
{
    StaticCanvas<2, 2> canvas;
    canvas.set_pixel(0, 0, Colourf{1.0f});
    canvas.set_pixel(0, 1, Colourf{1.0f});
    canvas.set_pixel(1, 0, Colourf{1.0f});
    canvas.set_pixel(1, 1, Colourf{1.0f});

    auto pixels = canvas.get_image();

    REQUIRE(canvas.get_height() == 2);
    REQUIRE(canvas.get_width() == 2);
    REQUIRE(canvas.channels == 3);

    REQUIRE(pixels.size() == 4);
    REQUIRE(pixels[0] == Colourf{1.0f});
    REQUIRE(pixels[1] == Colourf{1.0f});
    REQUIRE(pixels[2] == Colourf{1.0f});
    REQUIRE(pixels[3] == Colourf{1.0f});
}

TEST_CASE("[Canvas] - runtime canvas")
{
    RuntimeCanvas canvas{2, 2};
    canvas.set_pixel(0, 0, Colourf{1.0f});
    canvas.set_pixel(0, 1, Colourf{1.0f});
    canvas.set_pixel(1, 0, Colourf{1.0f});
    canvas.set_pixel(1, 1, Colourf{1.0f});

    auto pixels = canvas.get_image();

    REQUIRE(canvas.get_height() == 2);
    REQUIRE(canvas.get_width() == 2);
    REQUIRE(canvas.channels == 3);

    REQUIRE(pixels.size() == 4);
    REQUIRE(pixels[0] == Colourf{1.0f});
    REQUIRE(pixels[1] == Colourf{1.0f});
    REQUIRE(pixels[2] == Colourf{1.0f});
    REQUIRE(pixels[3] == Colourf{1.0f});
}
