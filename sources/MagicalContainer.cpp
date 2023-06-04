#include "MagicalContainer.hpp"


namespace ariel{

    void MagicalContainer::addElement(int element){
        for(int integer : container){
            if(integer == element){
                return;
            }
        }

        container.push_back(element);

        if(isPrime(element)){
            
            prime_container.push_back(new int(element));

        }

        sort(container.begin(),container.end());
        sort(prime_container.begin(), prime_container.end(), [](const int* first,const int* second) {return *first < *second;});
    }

    void MagicalContainer::removeElement(int element){
        bool find = false;
        for(auto iter=container.begin(); iter!=container.end();iter++){
            if(*iter == element){
                container.erase(iter);
                // i--;
                find = true;
                break;
            }
        }

        if(!find){
            throw std::runtime_error("This Element isnt in the container");
        }

        if(isPrime(element)){
            int* elementToRemove = new int(element);
            auto iterator = std::find(prime_container.begin(), prime_container.end(), elementToRemove);
            prime_container.erase(iterator);
            delete elementToRemove;
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