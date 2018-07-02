#include <iostream>
#include <vector>

int main(int argc, const char * argv[])
{
    std::vector<int> checkouts(181,0);
    std::vector<int> doubles;
    std::vector<int> singles;
    std::vector<int> trebles;
    
    for(int i = 1; i <= 20; i++)
    {
        singles.push_back(i);
        doubles.push_back(2*i);
        trebles.push_back(3*i);
    }
    doubles.push_back(50); // bullseye
    singles.push_back(25); // outer bull
    
    for(std::vector<int>::const_iterator i = doubles.begin(); i != doubles.end(); i++)
    {
        // single dart
        checkouts[*i]++;
        
        // two darts:
        // single
        for(std::vector<int>::const_iterator j = singles.begin(); j != singles.end(); j++)
            checkouts[*i + *j]++;
        // double
        for(std::vector<int>::const_iterator j = doubles.begin(); j != doubles.end(); j++)
            checkouts[*i + *j]++;
        // treble
        for(std::vector<int>::const_iterator j = trebles.begin(); j != trebles.end(); j++)
            checkouts[*i + *j]++;
        
        // three darts
        // single/single
        for(std::vector<int>::const_iterator j = singles.begin(); j != singles.end(); j++)
            for(std::vector<int>::const_iterator k = singles.begin(); k != singles.end(); k++)
                if(*j <= *k)
                    checkouts[*i + *j + *k]++;
        // single/double
        for(std::vector<int>::const_iterator j = singles.begin(); j != singles.end(); j++)
            for(std::vector<int>::const_iterator k = doubles.begin(); k != doubles.end(); k++)
                checkouts[*i + *j + *k]++;
        // single/treble
        for(std::vector<int>::const_iterator j = singles.begin(); j != singles.end(); j++)
            for(std::vector<int>::const_iterator k = trebles.begin(); k != trebles.end(); k++)
                checkouts[*i + *j + *k]++;
        // double/double
        for(std::vector<int>::const_iterator j = doubles.begin(); j != doubles.end(); j++)
            for(std::vector<int>::const_iterator k = doubles.begin(); k != doubles.end(); k++)
                if(*j <= *k)
                    checkouts[*i + *j + *k]++;
        // double/treble
        for(std::vector<int>::const_iterator j = doubles.begin(); j != doubles.end(); j++)
            for(std::vector<int>::const_iterator k = trebles.begin(); k != trebles.end(); k++)
                checkouts[*i + *j + *k]++;
        // treble/treble
        for(std::vector<int>::const_iterator j = trebles.begin(); j != trebles.end(); j++)
            for(std::vector<int>::const_iterator k = trebles.begin(); k != trebles.end(); k++)
                if(*j <= *k)
                    checkouts[*i + *j + *k]++;
    }
    
    int accum100 = 0, accumall = 0;
    
    for(int i = 1; i <= 170; i++)
    {
        std::cout << i << "|" << checkouts[i] << std::endl;
        if(i < 100) accum100 += checkouts[i];
        accumall += checkouts[i];
    }
    
    std::cout << accum100 << "|" << accumall << std::endl;
}
