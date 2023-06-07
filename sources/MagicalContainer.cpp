#include "MagicalContainer.hpp"


namespace ariel{

    void MagicalContainer::addElement(int element){

        auto iter = std::lower_bound(container.begin(),container.end(),element);

        //Checking if element already in the container
        if(iter != container.end() && *iter == element){
            return;
        }

        container.insert(iter,element);
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
}