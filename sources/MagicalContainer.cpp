#include "MagicalContainer.hpp"


namespace ariel{

    void MagicalContainer::addElement(int num_to_add){
        for(int element : container){
            if(num_to_add == element){
                return;
            }
        }

        container.push_back(num_to_add);

        if(isPrime(num_to_add)){
            int *pointer_prime = new int(num_to_add);
            prime_container.push_back( pointer_prime );

        }
        sort(container.begin(),container.end());
        sort(prime_container.begin(), prime_container.end(), [](const int* first,const int* second) {return *first < *second;});
    }

    void MagicalContainer::removeElement(int element){
        bool find = false;
        for(auto i=container.begin(); i!=container.end();i++){
            if(*i == element){
                container.erase(i);
                // i--;
                find = true;
                break;
            }
        }

        if(isPrime(element)){
            int* elementToRemove = new int(element);
            auto iterator = std::find(prime_container.begin(), prime_container.end(), elementToRemove);
            prime_container.erase(iterator);
            delete elementToRemove;
        }

        if(!find){
            throw std::runtime_error("This Element isnt in the container");
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