#include "image.hpp"

#include <catch2/catch.hpp>

TEST_CASE("[Image] - static image")
{
    StaticImage<2, 2> image;
    image(0, 0) = Colourf{1.0f};
    image(0, 1) = Colourf{1.0f};
    image(1, 0) = Colourf{1.0f};
    image(1, 1) = Colourf{1.0f};

    auto pixels = image.get_data();

    REQUIRE(image.height == 2);
    REQUIRE(image.width == 2);
    REQUIRE(image.channels == 3);

    REQUIRE(pixels.size() == 4);
    REQUIRE(pixels[0] == Colourf{1.0f});
    REQUIRE(pixels[1] == Colourf{1.0f});
    REQUIRE(pixels[2] == Colourf{1.0f});
    REQUIRE(pixels[3] == Colourf{1.0f});
}

TEST_CASE("[Canvas] - runtime canvas")
{
    DynamicImage<2, 2> image;
    image(0, 0) = Colourf{1.0f};
    image(0, 1) = Colourf{1.0f};
    image(1, 0) = Colourf{1.0f};
    image(1, 1) = Colourf{1.0f};

    auto pixels = image.get_data();

    REQUIRE(image.height == 2);
    REQUIRE(image.width == 2);
    REQUIRE(image.channels == 3);

    REQUIRE(pixels.size() == 4);
    REQUIRE(pixels[0] == Colourf{1.0f});
    REQUIRE(pixels[1] == Colourf{1.0f});
    REQUIRE(pixels[2] == Colourf{1.0f});
    REQUIRE(pixels[3] == Colourf{1.0f});
}
