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

            // copy constructor
            MagicalContainer(const MagicalContainer& other) = default;

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

            // return size of container
            int size();

            bool operator==(const MagicalContainer& other) const {
                return container == other.container;
            }

            // destructor
            ~MagicalContainer() {
                for (int* prime : prime_container) {
                    delete prime;
                }
            }

            // Copy assignment operator
            MagicalContainer& operator=(const MagicalContainer& other) {
                if (this != &other) {
                    // Perform deep copy of the container
                    container = other.container;
                }
                return *this;
            }

            // Move constructor
            MagicalContainer(MagicalContainer&& other) noexcept = default;

            // Move assignment operator
            MagicalContainer& operator=(MagicalContainer&& other) noexcept {
                if (this != &other) {
                    // Move the container from the other object
                    container = std::move(other.container);
                }
                return *this;
            }

            
        private:

            vector<int> container;

            vector<int*> prime_container;
            
            bool static isPrime(int element);


        public:

            // class FatherIterator {
            //     protected:
            //         MagicalContainer& container;
            //         size_t index;

            //     public:
            //         // Default constructor
            //         FatherIterator(MagicalContainer& container) : container(container), index(0) {}

            //         // Copy constructor
            //         FatherIterator(const FatherIterator& other) : container(other.container), index(other.index) {}

            //         // Return a new iterator at the beginning
            //         virtual FatherIterator begin() = 0;

            //         // Return an iterator that points to the end of the container (one past the last element)
            //         virtual FatherIterator end() = 0;

            //         // Dereference operator
            //         virtual int& operator*() const = 0;

            //         // Increment operator
            //         virtual FatherIterator& operator++() = 0;

            //         // Equality comparison operator
            //         virtual bool operator==(const FatherIterator& other) const = 0;

            //         // Inequality comparison operator
            //         virtual bool operator!=(const FatherIterator& other) const = 0;

            //         // Destructor
            //         virtual ~FatherIterator() = default;

            //         // Copy assignment operator
            //         FatherIterator& operator=(const FatherIterator& other) {
            //             if (this != &other) {
            //             container = other.container;
            //             index = other.index;
            //             }
            //             return *this;
            //         }

            //         // Move constructor
            //         FatherIterator(FatherIterator&& other) noexcept : container(other.container), index(other.index) {}

            //         // Move assignment operator
            //         FatherIterator& operator=(FatherIterator&& other) noexcept {
            //             if (this != &other) {
            //             container = std::move(other.container);
            //             index = other.index;
            //             }
            //             return *this;
            //         }
            // };

            class AscendingIterator{

                private:

                    MagicalContainer& container;
                    size_t index;

                public:

                    //defult constructor
                    AscendingIterator(MagicalContainer& container) : container(container),index(0){

                    }

                    //Copy constructor
                    AscendingIterator(const AscendingIterator& copy_container) : container(copy_container.container) , index(copy_container.index){}

                    // Return a new iterator at the beginning
                    AscendingIterator begin(){
                        this->index = 0;
                        return *this;
                    }

                    // Return an iterator that point to the end of the container (one past the last element)
                    AscendingIterator end(){
                        this->index = container.getContainer().size();
                        return *this;
                    }


                    int& operator*() const {
                        return container.getContainer()[index];
                    }

                    AscendingIterator& operator++(){

                        if(index == container.getContainer().size()){
                             throw std::runtime_error("Iterator already at end index");
                        }

                        // Increment the index
                        this->index++;
                        return *this;
                    }

                    bool operator==(const AscendingIterator& other) const{
                        return index == other.index;
                    }

                    bool operator!=(const AscendingIterator& other) const{
                        return index != other.index;
                    }

                    bool operator>(const AscendingIterator& other) const{
                        return index > other.index;
                    }

                    bool operator<(const AscendingIterator& other) const{
                        return index < other.index;
                    }


                    //Destructor
                    ~AscendingIterator() = default;

                    // Copy assignment operator
                    AscendingIterator& operator=(const AscendingIterator& other) {

                        if(container.getContainer() != other.container.getContainer()){
                            throw std::runtime_error("containers are not the same");
                        }

                        if (this != &other) {
                            container = other.container;
                            index = other.index;
                        }
                        return *this;
                    }

                    // Move constructor
                    AscendingIterator(AscendingIterator&& other) noexcept : container(other.container), index(other.index) {}

                    // Move assignment operator
                    AscendingIterator& operator=(AscendingIterator&& other) noexcept {
                        if (this != &other) {
                            container = std::move(other.container);
                            index = other.index;
                        }
                        return *this;
                    }

            };


            class SideCrossIterator{
                
                private:

                    MagicalContainer& container;
                    size_t idx_start;
                    size_t idx_end;
                    bool move_from_start;
                    

                public:

                    //defualt constructor
                    SideCrossIterator(MagicalContainer& container) : container(container),idx_start(0),idx_end(container.getContainer().size()-1) ,move_from_start(true){

                    } 

                    //Copy constructor
                    SideCrossIterator(const SideCrossIterator& other) : container(other.container),idx_start(other.idx_start),idx_end(other.idx_end) ,move_from_start(true){} //Copy constructor

                    // Return a new iterator at the beginning
                    SideCrossIterator begin(){
                        idx_start = 0;
                        idx_end = container.getContainer().size() - 1;
                        
                        return *this;

                    }

                    // Return an iterator that point to the end of the container (one past the last element)
                    SideCrossIterator end(){
                        this->idx_start = container.getContainer().size();
                        this->idx_end = 0;
                        
                        return *this;
                    }


                   int operator*() {
                        
                        if(move_from_start){
                            return container.getContainer()[idx_start];
                        }
                        
                        return container.getContainer()[idx_end];
                        
                    }


                    SideCrossIterator& operator++(){

                        if( idx_start == container.getContainer().size() && idx_end == 0){
                             throw std::runtime_error("++ error: iterator already at end index");
                        }
                        
                        if(move_from_start){
                            idx_start++;
                            move_from_start = false;
                        }
                        else{
                            idx_end--;
                            move_from_start = true;
                        }

                        if(idx_end < idx_start){
                            idx_end = 0;
                            idx_start = container.getContainer().size();
                            
                        }
                        return *this;
                    }

                    bool operator==(const SideCrossIterator& other) const{
                        // if(typeid(*this) != typeid(other)){
                        //     throw std::runtime_error("Cant check equal qon diffrent iterators");
                        // }
                        return (container == other.container) && (idx_start == other.idx_start) && (idx_end == other.idx_end);
                    }

                    bool operator!=(const SideCrossIterator& other) const{
                        return !(*this == other);
                    }

                    bool operator>(const SideCrossIterator& other) const{
                        // if (container.getContainer() != other.container.getContainer()) {
                        //     throw std::runtime_error("Comparison between iterators of different containers");
                        // }

                        return !move_from_start ? idx_start > other.idx_start : idx_end > other.idx_end;
                    }

                    bool operator<(const SideCrossIterator& other) const{
                        // if (container.getContainer() != other.container.getContainer()) {
                        //     throw std::runtime_error("Comparison between iterators of different containers");
                        // }
                        return !(*this == other) && !(*this > other);
                    }


                    //Destructor
                    ~SideCrossIterator() = default;

                    // Copy assignment operator
                    SideCrossIterator& operator=(const SideCrossIterator& other) {

                        if(container.getContainer() != other.container.getContainer()){
                            throw std::runtime_error("containers are not the same");
                        }

                        if (this != &other) {
                            container = other.container;
                            idx_start = other.idx_start;
                            idx_end = other.idx_end;
                            move_from_start = other.move_from_start;
                        }
                        return *this;
                    }

                    // Move constructor
                    SideCrossIterator(SideCrossIterator&& other) noexcept : container(other.container), idx_start(other.idx_start),idx_end(other.idx_end),move_from_start(other.move_from_start) {}

                    // Move assignment operator
                    SideCrossIterator& operator=(SideCrossIterator&& other) noexcept {
                        if (this != &other) {
                            container = std::move(other.container);
                            idx_start = other.idx_start;
                            idx_end = other.idx_end;
                            move_from_start = other.move_from_start;
                        }
                        return *this;
                    }
            };


            class PrimeIterator{

                private:

                    MagicalContainer& container;
                    size_t index;

                public:

                    //defualt constructor
                    PrimeIterator(MagicalContainer& container) : container(container) , index(0){
                        
                    } 

                    //Copy constructor
                    PrimeIterator(const PrimeIterator& other_container) : container(other_container.container) , index(other_container.index){} //Copy constructor


                    // Return a new iterator at the beginning
                    PrimeIterator begin(){
                        this->index = 0;
                        return *this;
                    }

                    // Return an iterator that point to the end of the container (one past the last element)
                    PrimeIterator end(){
                        this->index = container.getPrimeContainer().size();
                        return *this;
                    }


                    int& operator*(){
    
                        return *(container.getPrimeContainer()[index]);
                    }


                    PrimeIterator& operator++(){
                        
                        if( index == container.getPrimeContainer().size()){
                             throw std::runtime_error("++ error: iterator already at end index");
                        }

                        index++;
                        return *this;
                    }

                    bool operator==(const PrimeIterator& other) const{
                        return index == other.index;
                    }

                    bool operator!=(const PrimeIterator& other) const{
                        return index != other.index;
                    }

                    bool operator>(const PrimeIterator& other) const{
                        return index > other.index;
                    }

                    bool operator<(const PrimeIterator& other) const{
                        return index < other.index;
                    }

                    //Destructor
                    ~PrimeIterator() = default;


                    // Copy assignment operator
                    PrimeIterator& operator=(const PrimeIterator& other) {

                        if(container.getContainer() != other.container.getContainer()){
                            throw std::runtime_error("containers are not the same");
                        }

                        if (this != &other) {
                            container = other.container;
                            index = other.index;
                        }
                        return *this;
                    }

                    // Move constructor
                    PrimeIterator(PrimeIterator&& other) noexcept : container(other.container), index(other.index) {}

                    // Move assignment operator
                    PrimeIterator& operator=(PrimeIterator&& other) noexcept {
                        if (this != &other) {
                            container = std::move(other.container);
                            index = other.index;
                        }
                        return *this;
                    }

            };

            


    };
}



#endif