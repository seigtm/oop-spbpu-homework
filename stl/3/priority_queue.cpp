// Baranov Konstantin Pavlovich, group v5130904/20021.
// STL. Lab #3.1.

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <list>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>

namespace setm {

class priority_queue {
public:
    enum class priority : uint8_t {
        LOW,
        NORMAL,
        HIGH
    };

    struct element {
        std::string name;
    };

    using value_type = element;

    // Constructor with initializer lists for each priority level.
    priority_queue(std::initializer_list<value_type> elements_high = {},
                   std::initializer_list<value_type> elements_normal = {},
                   std::initializer_list<value_type> elements_low = {})
        : high{ elements_high }, normal{ elements_normal }, low{ elements_low } {}

    // Put element into the priority queue with specified priority.
    void put(value_type&& elem, priority prio) {
        auto& list{ get_list_for_priority(prio) };
        list.emplace_back(std::move(elem));
    }

    // Get the top priority element from the queue and remove it.
    [[nodiscard]] value_type get() {
        auto& list{ get_non_empty_list() };
        auto value{ std::move(list.front()) };

        list.pop_front();
        return value;
    }

    // Move all elements from low priority to high priority.
    void accelerate() {
        high.splice(high.end(), low);
    }

    // Get total size of the priority queue.
    [[nodiscard]] std::size_t size() const {
        return high.size() + normal.size() + low.size();
    }

    // Check if the priority queue is empty.
    [[nodiscard]] bool empty() const {
        return high.empty() && normal.empty() && low.empty();
    }

private:
    // Get the list corresponding to the given priority.
    [[nodiscard]] std::list<value_type>& get_list_for_priority(priority prio) {
        switch(prio) {
            case priority::LOW: return low;
            case priority::NORMAL: return normal;
            case priority::HIGH: return high;
            default: break;
        }
        std::unreachable();
    }

    // Get the first non-empty list based on priority.
    [[nodiscard]] std::list<value_type>& get_non_empty_list() {
        for(auto prio : { priority::HIGH, priority::NORMAL, priority::LOW })
            if(auto& list{ get_list_for_priority(prio) }; !list.empty())
                return list;

        throw std::out_of_range("queue is empty");
    }

    std::list<value_type> high;
    std::list<value_type> normal;
    std::list<value_type> low;
};

}  // namespace setm

int main() {
    using namespace std::literals::string_literals;

    setm::priority_queue pq = {
        { { "1"s }, { "2"s }, { "3"s } },
        { { "4"s }, { "5"s }, { "6"s } },
        { { "7"s }, { "8"s }, { "9"s } }
    };
    std::cout << "Queue size: " << pq.size() << '\n';
    while(!pq.empty()) {
        std::cout << pq.get().name << ' ';
    }
    std::cout << "\nQueue size: " << pq.size() << '\n';

    pq.put({ "10"s }, setm::priority_queue::priority::LOW);
    pq.put({ "11"s }, setm::priority_queue::priority::NORMAL);
    pq.put({ "12"s }, setm::priority_queue::priority::HIGH);
    std::cout << "\nQueue size: " << pq.size() << '\n';
    while(!pq.empty()) {
        std::cout << pq.get().name << ' ';
    }
    std::cout << "\nQueue size: " << pq.size() << '\n';

    pq.put({ "13"s }, setm::priority_queue::priority::LOW);
    pq.put({ "14"s }, setm::priority_queue::priority::NORMAL);
    pq.put({ "15"s }, setm::priority_queue::priority::HIGH);
    std::cout << "\nQueue size: " << pq.size() << '\n';
    pq.accelerate();
    while(!pq.empty()) {
        std::cout << pq.get().name << ' ';
    }
    std::cout << "\nQueue size: " << pq.size() << '\n';
}
