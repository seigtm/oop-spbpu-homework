// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #6.2.

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

namespace setm {

struct point {
    int x;
    int y;
};

struct shape {
    int vertex_num;
    std::vector<point> vertexes;
};

std::ostream& operator<<(std::ostream& out, const shape& s) {
    out << "{ vertex_num: " << s.vertex_num << ", vertexes: [ ";
    for(const auto& vertex : s.vertexes)
        out << "(" << vertex.x << ", " << vertex.y << ") ";

    return out << "] }";
}

void generate_random_shapes(std::vector<shape>& shapes, std::size_t count) {
    static std::default_random_engine gen{ std::random_device{}() };
    static std::uniform_int_distribution dist_vertex_num{ 3, 5 };
    static std::uniform_int_distribution dist_coordinate{ -100, 100 };

    std::generate_n(std::back_inserter(shapes), count, [] {
        const auto vertices_count{ dist_vertex_num(gen) };
        std::vector<point> vertices(vertices_count);

        for(auto& vertex : vertices) {
            vertex.x = dist_coordinate(gen);
            vertex.y = dist_coordinate(gen);
        }

        return shape{ vertices_count, vertices };
    });
}

[[nodiscard]] inline int total_vertices(const std::vector<shape>& shapes) {
    return std::accumulate(std::begin(shapes), std::end(shapes), 0,
                           [](int acc, const shape& s) {
                               return acc + s.vertex_num;
                           });
}

enum class shape_type : uint8_t {
    TRIANGLE = 3,
    RECTANGLE = 4,
    PENTAGON = 5,
    SQUARE = 14  // It's specifically not indicating the number of sides because it's a special case.
};

[[nodiscard]] inline bool is_square(const shape& s) {
    if(s.vertex_num != 4) return false;

    // Calculate the lengths of all sides
    const auto side1{ std::sqrt(std::pow(s.vertexes[0].x - s.vertexes[1].x, 2) + std::pow(s.vertexes[0].y - s.vertexes[1].y, 2)) };
    const auto side2{ std::sqrt(std::pow(s.vertexes[1].x - s.vertexes[2].x, 2) + std::pow(s.vertexes[1].y - s.vertexes[2].y, 2)) };
    const auto side3{ std::sqrt(std::pow(s.vertexes[2].x - s.vertexes[3].x, 2) + std::pow(s.vertexes[2].y - s.vertexes[3].y, 2)) };
    const auto side4{ std::sqrt(std::pow(s.vertexes[3].x - s.vertexes[0].x, 2) + std::pow(s.vertexes[3].y - s.vertexes[0].y, 2)) };

    // Check if all sides are equal
    return side1 == side2 && side2 == side3 && side3 == side4;
}

[[nodiscard]] inline std::size_t count_shapes(const std::vector<shape>& shapes, shape_type type) {
    // If the requested shape is square, check if all sides are equal.
    if(type == shape_type::SQUARE)
        return std::count_if(std::begin(shapes), std::end(shapes), [](const shape& s) {
            return s.vertex_num == 4 && is_square(s);
        });

    return std::count_if(std::begin(shapes), std::end(shapes), [type](const shape& s) {
        return s.vertex_num == static_cast<int>(type);
    });
}


void remove_shapes(std::vector<shape>& shapes, shape_type type) {
    shapes.erase(std::remove_if(std::begin(shapes), std::end(shapes), [type](const shape& s) {
                     if(type == shape_type::SQUARE || type == shape_type::RECTANGLE) {
                         return s.vertex_num == static_cast<int>(type) && is_square(s);
                     }
                     return s.vertex_num == static_cast<int>(type);
                 }),
                 std::end(shapes));
}

std::vector<setm::point> extract_vertices(const std::vector<setm::shape>& shapes) {
    std::vector<setm::point> vertices;
    std::transform(std::begin(shapes), std::end(shapes), std::back_inserter(vertices),
                   [](const setm::shape& s) { return s.vertexes[0]; });

    return vertices;
}

void reorder_shapes(std::vector<setm::shape>& shapes) {
    // Predicate to check if a shape is a triangle.
    auto is_triangle{ [](const setm::shape& s) {
        return s.vertex_num == static_cast<int>(setm::shape_type::TRIANGLE);
    } };
    // Predicate to check if a shape is a rectangle.
    auto is_rectangle{ [](const setm::shape& s) {
        return s.vertex_num == static_cast<int>(setm::shape_type::RECTANGLE) && !is_square(s);
    } };
    // Predicate to check if a shape is a pentagon.
    auto is_pentagon{ [](const setm::shape& s) {
        return s.vertex_num == static_cast<int>(setm::shape_type::PENTAGON);
    } };

    // Reorder the vector so that triangles come first, followed by squares,
    // then rectangles, and finally pentagons.
    auto triangle_end{ std::stable_partition(std::begin(shapes), std::end(shapes), is_triangle) };
    auto square_end{ std::stable_partition(triangle_end, std::end(shapes), is_square) };
    auto rectangle_end{ std::stable_partition(square_end, std::end(shapes), is_rectangle) };
    std::stable_partition(rectangle_end, std::end(shapes), is_pentagon);
}


}  // namespace setm

int main() {
    // 1. Generate 20 random shapes.
    std::vector<setm::shape> shapes;
    setm::generate_random_shapes(shapes, 5);
    std::cout << "1. Generated " << shapes.size() << " random shapes:\n";
    for(const auto& shape : shapes)
        std::cout << shape << '\n';

    // 2. Add 5 squares for tests to be fair.
    shapes.emplace_back(setm::shape{ 4, { { 0, 0 }, { 1, 0 }, { 1, 1 }, { 0, 1 } } });
    shapes.emplace_back(setm::shape{ 4, { { 2, 2 }, { 4, 2 }, { 4, 4 }, { 2, 4 } } });
    shapes.emplace_back(setm::shape{ 4, { { 5, 5 }, { 7, 5 }, { 7, 7 }, { 5, 7 } } });
    shapes.emplace_back(setm::shape{ 4, { { 8, 8 }, { 10, 8 }, { 10, 10 }, { 8, 10 } } });
    shapes.emplace_back(setm::shape{ 4, { { 11, 11 }, { 13, 11 }, { 13, 13 }, { 11, 13 } } });
    std::cout << "\n2. Added 5 squares for tests to be fair. And now there are " << shapes.size() << " shapes:\n";
    for(const auto& shape : shapes)
        std::cout << shape << '\n';

    // 3. Count total vertices.
    std::cout << "\n3. Total vertices: " << setm::total_vertices(shapes) << '\n';

    // 4. Count shapes.
    std::cout << "\n4. Shapes count:\n";
    std::cout << "\tTriangle shapes: " << setm::count_shapes(shapes, setm::shape_type::TRIANGLE) << '\n';
    std::cout << "\tSquare shapes: " << setm::count_shapes(shapes, setm::shape_type::SQUARE) << '\n';
    std::cout << "\tRectangle shapes: " << setm::count_shapes(shapes, setm::shape_type::RECTANGLE) << '\n';
    std::cout << "\tPentagon shapes: " << setm::count_shapes(shapes, setm::shape_type::PENTAGON) << '\n';

    // 5. Remove all pentagons.
    setm::remove_shapes(shapes, setm::shape_type::PENTAGON);
    std::cout << "\n5. After removing pentagons, there are " << shapes.size() << " shapes:\n";
    for(const auto& shape : shapes)
        std::cout << shape << '\n';

    // 6. Extract vertices from shapes.
    const auto extracted_vertices{ extract_vertices(shapes) };
    std::cout << "\n6. First vertices extracted from shapes:\n";
    for(const auto& vertex : extracted_vertices)
        std::cout << "Vertex: (" << vertex.x << ", " << vertex.y << ")\n";

    // 7. Reorder shapes so that triangles come first, followed by squares, then rectangles, and finally pentagons.
    setm::reorder_shapes(shapes);
    std::cout << "\n7. Reordered shapes:\n";
    for(const auto& shape : shapes)
        std::cout << shape << '\n';
}
