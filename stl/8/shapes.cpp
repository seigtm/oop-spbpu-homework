// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #8.2.

#include <algorithm>
#include <format>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <string_view>
#include <utility>

namespace setm {

enum class shape_type : uint8_t {
    CIRCLE,
    TRIANGLE,
    SQUARE,
    _COUNT  // To indicate the number of shapes.
};

class shape {
public:
    shape(double x, double y) noexcept
        : x{ x }, y{ y } {}

    virtual ~shape() noexcept = default;

    virtual void draw() const noexcept = 0;

    [[nodiscard]] bool is_more_left(const shape& other) const noexcept {
        return x < other.x;
    }

    [[nodiscard]] bool is_upper(const shape& other) const noexcept {
        return y > other.y;
    }

protected:
    const double x;
    const double y;
};

class circle : public shape {
public:
    using shape::shape;

    void draw() const noexcept override {
        std::cout << "Circle at (" << x << ", " << y << ")\n";
    }
};

class triangle : public shape {
public:
    using shape::shape;

    void draw() const noexcept override {
        std::cout << "Triangle at (" << x << ", " << y << ")\n";
    }
};

class square : public shape {
public:
    using shape::shape;

    void draw() const noexcept override {
        std::cout << "Square at (" << x << ", " << y << ")\n";
    }
};

template<typename Container>
void draw_shapes(const Container& shapes, std::string_view message) {
    std::cout << message << ":\n";
    for(const auto& shape : shapes)
        shape->draw();
    std::cout << '\n';
}

// Generates a random double within the specified range.
static double generate_random_double(double min, double max) noexcept {
    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_real_distribution dist{ min, max };

    return dist(gen);
}

// Generates a random shape type.
static setm::shape_type generate_random_shape_type() noexcept {
    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_int_distribution dist{ 0, static_cast<int>(setm::shape_type::_COUNT) - 1 };

    return static_cast<setm::shape_type>(dist(gen));
}

// Generates a random shape
shape* generate_random_shape() {
    const auto x{ generate_random_double(-100.0, 100.0) };
    const auto y{ generate_random_double(-100.0, 100.0) };
    const auto type{ generate_random_shape_type() };

    switch(type) {
        case shape_type::CIRCLE:
            return new circle(x, y);
        case shape_type::TRIANGLE:
            return new triangle(x, y);
        case shape_type::SQUARE:
            return new square(x, y);
        default:
            throw std::runtime_error("Unknown shape type.");
    }
}

}  // namespace setm

int main() {
    std::list<setm::shape*> shapes(10);
    std::generate(std::begin(shapes), std::end(shapes), [] { return setm::generate_random_shape(); });

    // Draw all shapes.
    setm::draw_shapes(shapes, std::format("All {} shapes", std::size(shapes)));

    // Sort and draw shapes.
    shapes.sort([](const auto& a, const auto& b) { return a->is_more_left(*b); });
    setm::draw_shapes(shapes, "Left to right");
    shapes.sort([](const auto& a, const auto& b) { return b->is_more_left(*a); });
    setm::draw_shapes(shapes, "Right to left");
    shapes.sort([](const auto& a, const auto& b) { return a->is_upper(*b); });
    setm::draw_shapes(shapes, "Top to bottom");
    shapes.sort([](const auto& a, const auto& b) { return b->is_upper(*a); });
    setm::draw_shapes(shapes, "Bottom to top");

    // Cleanup.
    for(auto shape : shapes)
        delete shape;
}