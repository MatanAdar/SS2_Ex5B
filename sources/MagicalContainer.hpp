#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>


using namespace std;

namespace ariel{

    class MagicalContainer{

        public:

            //defult constructor
            MagicalContainer() = default;

            vector<int>& getContainer(){
                return container;
            }

            void setContainer(vector<int>& new_container){
              container = new_container;
            }

            vector<int*>& getPrimeContainer(){
                return prime_container;
            }

            void addElement(int element);

            void removeElement(int element);

            void update_prime_container();

            // return size of container
            int size();

            bool operator==(const MagicalContainer& other) const {
                return container == other.container && prime_container == other.prime_container;
            }

            
        private:

            vector<int> container;

            vector<int*> prime_container;
            
            bool static isPrime(int element);


        public:

            class FatherIterator {
                private:
                    MagicalContainer& container;
                    size_t index;
                    bool move_from_start;

                public:
                    // Default constructor
                    FatherIterator(MagicalContainer& container) : container(container), index(0),move_from_start(true) {}

                    // Copy constructor
                    FatherIterator(const FatherIterator& other) : container(other.container), index(other.index) , move_from_start(other.move_from_start) {}

                    size_t getIndex() const{
                        return index;
                    }

                    void setIndex(size_t other){
                        index = other;
                    }

                    MagicalContainer& getContainerItr() const{
                        return container;
                    }

                    bool getMove_from_start() const{
                        return move_from_start;
                    }

                    void SetMove_from_start(bool other){
                        move_from_start = other;
                    }

                    // Return a new iterator at the beginning
                    virtual FatherIterator& begin() = 0;

                    // Return an iterator that points to the end of the container (one past the last element)
                    virtual FatherIterator& end() = 0;

                    // Dereference operator
                    virtual int& operator*() = 0;

                    // Increment operator
                    virtual FatherIterator& operator++() = 0;

                    // Equality comparison operator
                    bool operator==(const FatherIterator& other) const{
                        if(typeid(*this) != typeid(other)){
                            throw std::runtime_error("Cant check euqal on diffrent iterators");
                        }

                        return (this->container == other.container) && (this->index == other.index) && (move_from_start == other.move_from_start);
                    }

                    // Inequality comparison operator
                    bool operator!=(const FatherIterator& other) const {
                        return !(*this == other);
                    }

                    bool operator>(const FatherIterator& other) const{
                        return (index > other.index);
                    }

                    bool operator<(const FatherIterator& other) const{
                        // return index < other.index;
                        return !(*this == other) && !(*this > other);
                    }

                    // Destructor
                    virtual ~FatherIterator() = default;

                    // Copy assignment operator
                    FatherIterator& operator=(const FatherIterator& other) {
                        if(container.getContainer() != other.container.getContainer()){
                            throw std::runtime_error("containers are not the same");
                        }

                        if (this != &other) {
                            container = other.container;
                            index = other.index;
                            move_from_start = other.move_from_start;
                        }
                        return *this;
                    }

                    // Move constructor
                    FatherIterator(FatherIterator&& other) noexcept : container(other.container), index(other.index) , move_from_start(other.move_from_start) {
                        other.index = 0;
                        other.move_from_start = false;
                    }

                    // Move assignment operator
                    FatherIterator& operator=(FatherIterator&& other) noexcept {
                        if (this != &other) {
                            container = std::move(other.container);
                            index = other.index;
                            move_from_start = other.move_from_start;
                            other.index = 0;
                            other.move_from_start = false;
                        }
                        return *this;
                    }
            };

            class AscendingIterator : public FatherIterator{

                public:
 
                    AscendingIterator(MagicalContainer& container);

                    AscendingIterator& begin() override;

                    AscendingIterator& end() override;

                    int& operator*() override;

                    AscendingIterator& operator++() override;
            };


            class SideCrossIterator : public FatherIterator{
                    
                public:

                    SideCrossIterator(MagicalContainer& container);

                    SideCrossIterator& begin() override;

                    SideCrossIterator& end() override;

                    int& operator*() override;

                    SideCrossIterator& operator++() override;
                    
            };


            class PrimeIterator : public FatherIterator{

                public:

                    PrimeIterator(MagicalContainer& container);

                    PrimeIterator& begin() override;

                    PrimeIterator& end() override;

                    int& operator*() override;

                    PrimeIterator& operator++() override;
            };

    };
}



#endif