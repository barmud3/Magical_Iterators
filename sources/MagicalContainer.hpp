#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
namespace ariel{};


class MagicalContainer{
private:
    vector<int> magicCon;
    vector<int> sortMagicCon;
    vector<int> primeMagicCon;
public:

    // Default constructor
    MagicalContainer() {}


    // Copy constructor
    MagicalContainer(const MagicalContainer& other) : magicCon(other.magicCon) , sortMagicCon(other.sortMagicCon) , primeMagicCon(other.primeMagicCon){
    }

    // Destructor
    ~MagicalContainer() {}
    
    // Move constructor
    MagicalContainer(MagicalContainer&& other) noexcept
    : magicCon(std::move(other.magicCon)),
        sortMagicCon(std::move(other.sortMagicCon)),
        primeMagicCon(std::move(other.primeMagicCon)) {}

    // Move assignment operator
    MagicalContainer& operator=(MagicalContainer&& other) noexcept {
        if (this != &other) {
            magicCon = std::move(other.magicCon);
            sortMagicCon = std::move(other.sortMagicCon);
            primeMagicCon = std::move(other.primeMagicCon);
        }
        return *this;
    }
    // Assignment operator
    MagicalContainer& operator=(const MagicalContainer& other) {
        if (this != &other) {
            magicCon = other.magicCon;
            sortMagicCon = other.sortMagicCon;
            primeMagicCon = other.primeMagicCon;
        }
        return *this;
    }

    void addElement(int element) {
        magicCon.emplace_back(element);
        addElementSort(element);
        addElementPrime(element);
    }

    void addElementSort(int element)
    {
        auto insertPosition = lower_bound(sortMagicCon.begin(), sortMagicCon.end(), element);
        sortMagicCon.emplace(insertPosition, element);
    }

    void addElementPrime(int element)
    {
        if (isPrime(element))
        {
            //cout << "IS PRIME : " << element << endl;
            auto insertPosition = lower_bound(primeMagicCon.begin(), primeMagicCon.end(), element);
            primeMagicCon.emplace(insertPosition, element);
        }
    }

    static bool isPrime(int element)
    {
        if (element <= 1)
        {
            return false;
        }
        
        for (int i = 2; i <= sqrt(element); i++)
        {
            if(element % i == 0)
            {
                return false;
            }
        }
        return true;
        
    }

    void removeElement(int element) {
        magicCon.erase(std::remove(magicCon.begin(), magicCon.end(), element), magicCon.end());
    }

    std::vector<int>::size_type size() const {
    return magicCon.size();
    }

    class AscendingIterator  {

	    private:
        MagicalContainer& myContainer;
        int index;

	    public:

		AscendingIterator (MagicalContainer& container)
			: myContainer(container) , index(0){
		}

        AscendingIterator (MagicalContainer& container, int index)
			: myContainer(container) , index(index){
		}

		int operator*() {
           
			return this->myContainer.sortMagicCon[static_cast<size_t>(index)];
		}

		// ++i;
		AscendingIterator& operator++() {
			//++pointer_to_current_node;
			++ this->index;
            return *this;
		}

		// i++;
		AscendingIterator operator++(int) {
            AscendingIterator temp = *this;
			this->index++;
            return temp;
		}

		bool operator==(const AscendingIterator&  rhs) const {
			return (this->index == rhs.index);
		}

		bool operator!=(const AscendingIterator& rhs) const {
			return !(*this == rhs);
		}

        bool operator>(const AscendingIterator& rhs) const {
			return this->index > rhs.index;
		}

        bool operator<(const AscendingIterator& rhs) const {
			return this->index < rhs.index;
		}

        AscendingIterator begin()
        {
            return AscendingIterator(this->myContainer);
        }

        AscendingIterator end() 
        {
            return AscendingIterator(this->myContainer , static_cast<int>(this->myContainer.size()));
        }

	}; 



    class SideCrossIterator{

        private:

        const MagicalContainer& container;
        int index;

        public:

        SideCrossIterator (const MagicalContainer& container)
			: container(container) , index(0) {
		}

        SideCrossIterator (const MagicalContainer& container, int index)
			: container(container) , index(index) {
		}

        int operator*() const {
			//return *pointer_to_current_node;
			if (this->index%2 == 0) // cross side will be left
            {
                return this->container.magicCon[static_cast<size_t>(this->index/2)]; 
            }
            // cross side will be right
            size_t disFromEnd = static_cast<size_t>(this->container.size() -1 - static_cast<size_t>(this->index/2));
            return this->container.magicCon[disFromEnd];
		}

        // ++i;
		SideCrossIterator& operator++() {
			++ this->index;
            return *this;
		}

		// i++;
		SideCrossIterator operator++(int) {
			SideCrossIterator temp = *this;
            this->index++;
            return temp;
		}

        bool operator==(const SideCrossIterator&  rhs) const {
			return (this->index == rhs.index);
		}

		bool operator!=(const SideCrossIterator& rhs) const {
			return !(*this == rhs);
		}

        bool operator>(const SideCrossIterator& rhs) const {
			return this->index > rhs.index;
		}

        bool operator<(const SideCrossIterator& rhs) const {
			return this->index < rhs.index;
		}
        
        SideCrossIterator begin()
        {
        return SideCrossIterator{this->container};
        }

        SideCrossIterator end() {
        return SideCrossIterator{this->container, static_cast<int>(this->container.size())};

        }

    };

    
    class PrimeIterator{

        private:

        const MagicalContainer& container;
        int index;

        public:

        PrimeIterator (const MagicalContainer& container)
			: container(container) , index(0) {
		}

        PrimeIterator (const MagicalContainer& container, int index)
			: container(container) , index(index) {
		}

		int operator*() const {
            return this->container.primeMagicCon[static_cast<size_t>(index)];
		}

		// ++i;
		PrimeIterator& operator++() {
            if (this->index < this->container.primeMagicCon.size())
            {
                ++ this->index;
            }
            return *this;
		}

		// i++;
		PrimeIterator operator++(int) {
            PrimeIterator temp = *this;
            if (this->index < this->container.primeMagicCon.size())
            {
			    this->index++;
            }
            return temp;
		}

		bool operator==(const PrimeIterator&  rhs) const {
			return (this->index == rhs.index);
		}

		bool operator!=(const PrimeIterator& rhs) const {
			return !(*this == rhs);
		}

        bool operator>(const PrimeIterator& rhs) const {
			return this->index > rhs.index;
		}

        bool operator<(const PrimeIterator& rhs) const {
			return this->index < rhs.index;
		}

        PrimeIterator begin()
        {
        return PrimeIterator{this->container};
        }

        PrimeIterator end() {
        return PrimeIterator{this->container ,static_cast<int>(this->container.primeMagicCon.size())};
        }
    };
};
