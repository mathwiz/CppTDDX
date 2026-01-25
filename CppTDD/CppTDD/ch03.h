//
//  ch03.h
//  CppTDD
//
//  Created by Yohan Lee on 1/24/26.
//

#include <cstdio>

void ex3_1() {
    int gettysburg{1863};
    printf("gettysburg: %d\n", gettysburg);
    int *gettysburg_address = &gettysburg;
    printf("&gettysburg: %p\n", gettysburg_address);
}


void ex3_2() {
    int gettysburg{1863};
    int *gettysburg_address = &gettysburg;
    printf("Value at gettysburg_address: %d\n", *gettysburg_address);
    printf("gettysburg_address: %p\n", gettysburg_address);
    *gettysburg_address = 90210;
    printf("Value at gettysburg_address: %d\n", *gettysburg_address);
    printf("gettysburg_address: %p\n", gettysburg_address);
}


struct ClockOfTheLongNow {
    ClockOfTheLongNow() {
    }
    ClockOfTheLongNow(long y) {
        if(!set_year(y)) {
            this->year = DEFAULT * -1;
        }
    }
    void add_year() {
        this->year++;
    }
    bool set_year(long new_year) {
        if (new_year < 2026) return false;
        this->year = new_year;
        return true;
    }
    long get_year() const {
        return this->year;
    }
    bool is_leap_year() {
        if (this->get_year() % 4 > 0) return false;
        if (this->get_year() % 100 > 0) return true;
        if (this->get_year() % 400 > 0) return false;
        return true;
    }
private:
    long DEFAULT = 2000;
    long year = DEFAULT;
};

void ex3_3() {
    ClockOfTheLongNow clock{};
    ClockOfTheLongNow* clock_ptr = &clock;
    printf("Clock address: %p\n", clock_ptr);
    printf("Clock year: %lu\n", clock_ptr->get_year());
    clock_ptr->set_year(2026);
    printf("Clock year: %lu\n", clock_ptr->get_year());
}


struct College {
    char name[256];
};

void print_name(College* college_ptr) {
    printf("%s College\n", college_ptr->name);
}

void print_names(College* colleges, size_t n_colleges) {
    for (size_t i=0; i < n_colleges; i++)
        printf("%s College\n", colleges[i].name);
}

void ex3_4() {
    College best_colleges[] = { "Magdalen", "Nuffield", "Kellogg" };
    print_name(best_colleges);
    print_name(&best_colleges[1]);
    print_name(&best_colleges[2]);
}


void ex3_5() {
    College best_colleges[] = { "Magdalen", "Nuffield", "Kellogg" };
    print_names(best_colleges, sizeof(best_colleges) / sizeof(College));
}


void ex3_6() {
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char* upper_ptr = upper;
    
    lower[3] = 'd';
    upper_ptr[3] = 'D';
    
    char letter_d = lower[3];
    char letter_D = upper_ptr[3];
    
    printf("lower: %s, upper: %s\n", lower, upper);
    printf("lower[3]: %c, upper_ptr[3]: %c\n", letter_d, letter_D);
}


void ex3_7() {
    char lower[] = "abc?e";
    char upper[] = "ABC?E";
    char* upper_ptr = upper;
    
    *(lower + 3) = 'd';
    *(upper_ptr + 3) = 'D';
    
    char letter_d = *(lower + 4);
    char letter_D = *(upper_ptr + 4);
    
    printf("lower: %s, upper: %s\n", lower, upper);
    printf("lower[4]: %c, upper_ptr[4]: %c\n", letter_d, letter_D);
}


void add_year_to_clock(ClockOfTheLongNow& clock) {
    clock.set_year(clock.get_year() + 1);
}

void ex3_8() {
    ClockOfTheLongNow clock{2026};
    printf("The year is %lu.\n", clock.get_year());
    add_year_to_clock(clock);
    printf("The year is %lu.\n", clock.get_year());
}


struct Element {
    Element* next{};
    void insert_after(Element* new_elem) {
        new_elem->next = next;
        this->next = new_elem;
    }
    char prefix[2];
    short operating_number;
};

void ex3_10() {
    Element trooper1, trooper2, trooper3;
    trooper1.prefix[0] = 'T';
    trooper1.prefix[1] = 'K';
    trooper1.operating_number = 421;
    trooper1.insert_after(&trooper2);
    trooper2.prefix[0] = 'F';
    trooper2.prefix[1] = 'N';
    trooper2.operating_number = 2187;
    trooper2.insert_after(&trooper3);
    trooper3.prefix[0] = 'L';
    trooper3.prefix[1] = 'S';
    trooper3.operating_number = 005;
    
    for (Element *cursor = &trooper1; cursor; cursor = cursor->next) {
        printf("Stormtrooper %c%c-%d\n",
               cursor->prefix[0],
               cursor->prefix[1],
               cursor->operating_number);
    }
}


void ex3_11() {
    int original = 100;
    int& original_ref = original;
    printf("Original:   %d\n", original);
    printf("Reference:  %d\n", original_ref);
    
    int new_value = 200;
    original_ref = new_value;
    printf("Original:   %d\n", original);
    printf("New Value:  %d\n", new_value);
    printf("Reference:  %d\n", original_ref);
}


struct Avout {
    Avout(const char* name, long year_of_apert)
    : name { name }, apert { year_of_apert } {
    }
    void announce() const {
        printf("My name is %s and my next apert is %lu.\n", name, apert.get_year());
    }
private:
    const char* name;
    ClockOfTheLongNow apert;
};


void ex3_18() {
    Avout raz{ "Erasmus", 3010 };
    Avout jaz{ "Jad", 4400 };
    raz.announce();
    jaz.announce();
}
