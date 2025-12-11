#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include "header.h"


int main()
{
	Array *test;
	Movie mov;

	//Initialise function
	test = initialise(5);
    assert(test != NULL);
    assert(test->c_size == 0);
    assert(test->t_size == 5);

    //Insertion function
    mov.mov_id = 1;
	strcpy(mov.mov_name,"Milana");
	strcpy(mov.mov_genre,"Rom-com");
	mov.mov_rating = 9.8;
	mov.mov_rel_year = 2020;
	assert(insert(test,mov));

	mov.mov_id = 2;
	strcpy(mov.mov_name,"Kantara");
	strcpy(mov.mov_genre,"Thriller");
	mov.mov_rating = 9.5;
	mov.mov_rel_year = 2022;
	assert(insert(test,mov));

	mov.mov_id = 3;
	strcpy(mov.mov_name,"Kirik Party");
	strcpy(mov.mov_genre,"Rom-com");
	mov.mov_rating = 9.9;
	mov.mov_rel_year = 2020;
	assert(insert(test,mov));

	mov.mov_id = 4;
	strcpy(mov.mov_name,"KGF");
	strcpy(mov.mov_genre,"Action");
	mov.mov_rating = 9.1;
	mov.mov_rel_year = 2020;
	assert(insert(test,mov));

	mov.mov_id = 5;
	strcpy(mov.mov_name,"Yuvaratna");
	strcpy(mov.mov_genre,"Rom-com");
	mov.mov_rating = 9.6;
	mov.mov_rel_year = 2023;
	assert(insert(test,mov));

	//assert(test->c_size == 5);
	//assert(test->c_size == test->t_size);

	/*mov.mov_id = 6;
	strcpy(mov.mov_name,"Bahubali");
	strcpy(mov.mov_genre,"Historic");
	mov.mov_rating = 9.6;
	mov.mov_rel_year = 2024;
	assert(insert(test,mov));*/

	assert(test->arr[4].mov_id == 5);

	
	//Movies released in a year
	assert(movie_count_by_year(test, 2020) == 3);
	assert(movie_count_by_year(test, 2023) == 1);


	//Display the title with highest rating
	highest_rating(test);

	//Details of movie with genre as action
	display(test,"Action",9);

	return 0;

}