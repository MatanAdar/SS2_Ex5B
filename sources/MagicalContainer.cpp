#include "MagicalContainer.hpp"


namespace ariel{

//MagicalContainer functions

    void MagicalContainer::addElement(int element){

        auto iter = std::lower_bound(container.begin(),container.end(),element);

        //Checking if element already in the container
        if(iter != container.end() && *iter == element){
            return;
        }

        iter = container.insert(iter,element);
        update_prime_container();
    }

    void MagicalContainer::removeElement(int element){

        auto iter = std::lower_bound(container.begin(),container.end(),element);

        if(iter == container.end() || *iter != element){
            throw std::runtime_error("Elements not found");
        }
        container.erase(iter);
        update_prime_container();
    }

    void MagicalContainer::update_prime_container(){

        prime_container.clear();
        for(size_t i = 0; i<container.size();i++){
            if(isPrime(container[i])){
                prime_container.push_back(&container[i]);
            }
        }
     }

    // return size of container
    int MagicalContainer::size(){
        return (int)container.size();
    }

    bool MagicalContainer::isPrime(int element){
                    
        if(element <= 1){
            return false;
        }

        if(element == 2 || element == 3){
            return true;
        }

        for(int i=2 ; i<=sqrt(element) ; i++){
            if(element % i == 0){
                return false;
            }
        }

        return true;
    }


//AscendingIterator Functions
    
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& container) : FatherIterator(container){

    }

    // Return a new iterator at the beginning
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin(){
        this->setIndex(0);
        return *this;
    }

    // Return an iterator that point to the end of the container (one past the last element)
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end(){
        this->setIndex(this->getContainerItr().getContainer().size());
        return *this;
    }


    int& MagicalContainer::AscendingIterator::operator*(){
        return this->getContainerItr().getContainer()[this->getIndex()];
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){

        if(this->getIndex() == this->getContainerItr().getContainer().size()){
                throw std::runtime_error("Iterator already at end index");
        }

        // Increment the index
        this->setIndex(this->getIndex()+1);
        return *this;
    }



//SideCrossIterator functions

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container) : FatherIterator(container){

    }

    // Return a new iterator at the beginning
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin(){
        this->SetMove_from_start(true);
        this->setIndex(0);
        return *this;
    }

    // Return an iterator that point to the end of the container (one past the last element)
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end(){
        this->setIndex(this->getContainerItr().getContainer().size());
        this->SetMove_from_start(false);
        return *this;
    }

    int& MagicalContainer::SideCrossIterator::operator*(){

        if (this->getMove_from_start()) {
            return this->getContainerItr().getContainer()[this->getIndex()];
        }
        
        return this->getContainerItr().getContainer()[this->getContainerItr().getContainer().size() - this->getIndex()];
        
        
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){

        size_t containerSize = this->getContainerItr().getContainer().size();

        if (this->getIndex() == containerSize) {
            throw std::runtime_error("Iterator already at end index");
        }
        //checking if container size is odd
        if (containerSize % 2 != 0) {
            if (this->getMove_from_start()) {  //checking if we on the left size
                this->SetMove_from_start(false);
                (this->getIndex() == containerSize / 2) ? this->setIndex(containerSize) : this->setIndex(this->getIndex() + 1);
            } else { // we on the right size
                this->SetMove_from_start(true);
            }
        } else {  //container size is even
            if (this->getMove_from_start()) {
                this->SetMove_from_start(false);
                this->setIndex(this->getIndex() + 1);
            } else {
                this->getIndex() == containerSize / 2 ? this->setIndex(containerSize) : this->SetMove_from_start(true);
                
            }
        }


        return *this;

    }


//PrimeIterator functions

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container) : FatherIterator(container){
                        
    }

    // Return a new iterator at the beginning(index at 0)
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin(){
        this->setIndex(0);
        return *this;
    }

    // Return an iterator that point to the end of the container (one past the last element)
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end(){
        this->setIndex(this->getContainerItr().getPrimeContainer().size());
        return *this;
    }

    int& MagicalContainer::PrimeIterator::operator*(){

        return *(this->getContainerItr().getPrimeContainer()[this->getIndex()]);
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
        
        if( this->getIndex() == this->getContainerItr().getPrimeContainer().size()){
                throw std::runtime_error("++ error: iterator already at end index");
        }
        //increment the index by 1
        this->setIndex(this->getIndex()+1);
        return *this;
    }

}