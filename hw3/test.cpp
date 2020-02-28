#include "todolist.h"
#include "gtest/gtest.h"

class ArrayListTest : public testing::Test {
protected:

	void normalSetUp() {
		list.push_back(0, "0a", false);
		list.push_back(1, "1a", false);
		list.push_back(2, "2a", false);
		list.push_back(3, "3a", false);
		list.push_back(4, "4a", false);
	}

	void singleListSetUp() {
		list.push_back(0, "0a", false);
		list.push_back(0, "0b", false);
		list.push_back(0, "0c", false);
		list.push_back(0, "0d", false);
		list.push_back(0, "0e", false);
	}

	void prioritySetUp() {
		list.push_back(0, "0a", true);
		list.push_back(1, "1a", false);
		list.push_back(2, "2a", true);
		list.push_back(3, "3a", false);
		list.push_back(4, "4a", true);
	}
	DailyTodoList list;
};

TEST_F(ArrayListTest, pushBackTest) {
	normalSetUp();

	//Check if everything is correct
	EXPECT_EQ(list.getNormalVal(0,0), "0a");
	EXPECT_EQ(list.getNormalVal(1,0), "1a");
	EXPECT_EQ(list.getNormalVal(2,0), "2a");
	EXPECT_EQ(list.getNormalVal(3,0), "3a");
	EXPECT_EQ(list.getNormalVal(4,0), "4a");
	
	//Check number of items
	for(int i = 0; i < 5; i++) {
		EXPECT_EQ(list.numItemsOnDay(i), 1);
	}

	//Check other data
	EXPECT_EQ(list.numDays(), 5);
	EXPECT_EQ(list.numPriorityItems(),0);
}

TEST_F(ArrayListTest, insertTest) {
	singleListSetUp();
	
	//Make some inserts
	list.insert(0, 3, "0dd", false);
	list.insert(0, 6, "0f", false);
	list.insert(0, 0, "0aa", false);

	//Check values
	EXPECT_EQ(list.getNormalVal(0,0), "0aa");
	EXPECT_EQ(list.getNormalVal(0,1), "0a");
	EXPECT_EQ(list.getNormalVal(0,2), "0b");
	EXPECT_EQ(list.getNormalVal(0,3), "0c");
	EXPECT_EQ(list.getNormalVal(0,4), "0dd");
	EXPECT_EQ(list.getNormalVal(0,5), "0d");
	EXPECT_EQ(list.getNormalVal(0,6), "0e");
	EXPECT_EQ(list.getNormalVal(0,7), "0f");
	EXPECT_EQ(list.numItemsOnDay(0), 8);

}

TEST_F(ArrayListTest, insertException) {
	normalSetUp();
	//Throw exceptions
	EXPECT_THROW(list.insert(0, 5, "Out of range", false), std::out_of_range);
	EXPECT_THROW(list.insert(10, 5, "Out of range", false), std::out_of_range);
}

TEST_F(ArrayListTest, removeTest) {
	normalSetUp();

	//Remove two and check everything
	list.remove(1, 0);
	list.remove(3, 0);

	//Check values
	EXPECT_EQ(list.getNormalVal(0,0), "0a");
	EXPECT_EQ(list.empty(1), true);
	EXPECT_EQ(list.getNormalVal(2,0), "2a");
	EXPECT_EQ(list.empty(3), true);
	EXPECT_EQ(list.getNormalVal(4,0), "4a");
	
	//Check number of items
	EXPECT_EQ(list.numItemsOnDay(0), 1);
	EXPECT_EQ(list.numItemsOnDay(1), 0);
	EXPECT_EQ(list.numItemsOnDay(2), 1);
	EXPECT_EQ(list.numItemsOnDay(3), 0);
	EXPECT_EQ(list.numItemsOnDay(4), 1);

	//Check other data
	EXPECT_EQ(list.numDays(), 5);
	EXPECT_EQ(list.numPriorityItems(),0);
}

TEST_F(ArrayListTest, singleListTest) {
	//Test removing and adding to a single list
	singleListSetUp();

	//Check setup
	EXPECT_EQ(list.getNormalVal(0,0), "0a");
	EXPECT_EQ(list.getNormalVal(0,1), "0b");
	EXPECT_EQ(list.getNormalVal(0,2), "0c");
	EXPECT_EQ(list.getNormalVal(0,3), "0d");
	EXPECT_EQ(list.getNormalVal(0,4), "0e");
	EXPECT_EQ(list.numItemsOnDay(0), 5);

	//Remove some values
	EXPECT_NO_THROW(list.remove(0,0));
	EXPECT_NO_THROW(list.remove(0,1));
	EXPECT_NO_THROW(list.remove(0,2));

	//Check values
	EXPECT_EQ(list.getNormalVal(0,0), "0b");
	EXPECT_EQ(list.getNormalVal(0,1), "0d");
	EXPECT_EQ(list.numItemsOnDay(0), 2);
}

TEST_F(ArrayListTest, removeExceptions) {
	singleListSetUp();

	//Check exceptions
	EXPECT_THROW(list.remove(0,7), std::out_of_range);
	EXPECT_THROW(list.remove(4,0), std::out_of_range);
	EXPECT_THROW(list.remove(10,0), std::out_of_range);
}

TEST_F(ArrayListTest, outOfRangeExceptions) {
	normalSetUp();

	//Check read access violation exceptions
	EXPECT_THROW(list.numItemsOnDay(5), std::out_of_range);
	EXPECT_THROW(list.empty(5), std::out_of_range);
	EXPECT_THROW(list.getNormalVal(5,0), std::out_of_range);
}

TEST_F(ArrayListTest, ResizingArray) {
	normalSetUp();
	
	//Resize array
	EXPECT_NO_THROW(list.insert(5, 0, "5a", false));

	//Make sure everything copied over
	EXPECT_EQ(list.getNormalVal(0,0), "0a");
	EXPECT_EQ(list.getNormalVal(1,0), "1a");
	EXPECT_EQ(list.getNormalVal(2,0), "2a");
	EXPECT_EQ(list.getNormalVal(3,0), "3a");
	EXPECT_EQ(list.getNormalVal(4,0), "4a");
	EXPECT_EQ(list.getNormalVal(5,0), "5a");
	//Rest of the list is empty
	for(int i = 6; i < 10; i++)
	{
		EXPECT_EQ(list.empty(i), true);
	}
	//Check size
	EXPECT_EQ(list.numDays(), 10);

	//Make sure it doubles corectly
	EXPECT_NO_THROW(list.insert(20, 0, "20a", false));
	EXPECT_EQ(list.numDays(), 40);
}

TEST_F(ArrayListTest, priorityTest) {
	prioritySetUp();

	//Check normal
	EXPECT_EQ(list.getNormalVal(0,0), "0a");
	EXPECT_EQ(list.getNormalVal(1,0), "1a");
	EXPECT_EQ(list.getNormalVal(2,0), "2a");
	EXPECT_EQ(list.getNormalVal(3,0), "3a");
	EXPECT_EQ(list.getNormalVal(4,0), "4a");
	//Check priority
	EXPECT_EQ(list.getPriorityVal(0), "0a");
	EXPECT_EQ(list.getPriorityVal(1), "2a");
	EXPECT_EQ(list.getPriorityVal(2), "4a");
	EXPECT_EQ(list.numPriorityItems(), 3);
}

TEST_F(ArrayListTest, priorityRemoveTest) {
	prioritySetUp();

	//Add a few more priority values
	list.push_back(7, "7a", true);
	list.push_back(8, "8a", true);
	list.push_back(9, "9a", true);

	//Check values
	EXPECT_EQ(list.getPriorityVal(0), "0a");
	EXPECT_EQ(list.getPriorityVal(1), "2a");
	EXPECT_EQ(list.getPriorityVal(2), "4a");
	EXPECT_EQ(list.getPriorityVal(3), "7a");
	EXPECT_EQ(list.getPriorityVal(4), "8a");
	EXPECT_EQ(list.getPriorityVal(5), "9a");
	EXPECT_EQ(list.numPriorityItems(), 6);

	//Remove priority values
	EXPECT_NO_THROW(list.remove(0,0));
	EXPECT_NO_THROW(list.remove(7,0));
	EXPECT_NO_THROW(list.remove(9,0));

	//Check priority values
	EXPECT_EQ(list.getPriorityVal(0), "2a");
	EXPECT_EQ(list.getPriorityVal(1), "4a");
	EXPECT_EQ(list.getPriorityVal(2), "8a");
	EXPECT_THROW(list.getPriorityVal(3), std::out_of_range);
	EXPECT_EQ(list.numPriorityItems(), 3);

	//Check all normal values
	EXPECT_THROW(list.getNormalVal(0,0), std::out_of_range);
	EXPECT_EQ(list.getNormalVal(1,0), "1a");
	EXPECT_EQ(list.getNormalVal(2,0), "2a");
	EXPECT_EQ(list.getNormalVal(3,0), "3a");
	EXPECT_EQ(list.getNormalVal(4,0), "4a");
	EXPECT_THROW(list.getNormalVal(7,0), std::out_of_range);
	EXPECT_EQ(list.getNormalVal(8,0), "8a");
	EXPECT_THROW(list.getNormalVal(9,0), std::out_of_range);
}

TEST_F(ArrayListTest, removeEverything)
{
    prioritySetUp();

    //Add a few more priority values
    list.push_back(7, "7a", true);
    list.push_back(8, "8a", true);
    list.push_back(9, "9a", true);

    //this is the first round of removing
    EXPECT_NO_THROW(list.remove(0, 0));
    EXPECT_NO_THROW(list.remove(1, 0));
    EXPECT_NO_THROW(list.remove(2, 0));
    EXPECT_NO_THROW(list.remove(3, 0));
    EXPECT_NO_THROW(list.remove(4, 0));
    EXPECT_NO_THROW(list.remove(7, 0));
    EXPECT_NO_THROW(list.remove(8, 0));
    EXPECT_NO_THROW(list.remove(9, 0));

    //adding back
    list.push_back(0, "0a", true);
    list.push_back(1, "1a", false);
    list.push_back(2, "2a", true);
    list.push_back(3, "3a", false);
    list.push_back(4, "4a", true);
    list.push_back(7, "7a", true);
    list.push_back(8, "8a", true);
    list.push_back(9, "9a", true);

    //Check values
    EXPECT_EQ(list.getPriorityVal(0), "0a");
    EXPECT_EQ(list.getPriorityVal(1), "2a");
    EXPECT_EQ(list.getPriorityVal(2), "4a");
    EXPECT_EQ(list.getPriorityVal(3), "7a");
    EXPECT_EQ(list.getPriorityVal(4), "8a");
    EXPECT_EQ(list.getPriorityVal(5), "9a");
    EXPECT_EQ(list.numPriorityItems(), 6);

    //Remove priority values
    EXPECT_NO_THROW(list.remove(0, 0));
    EXPECT_NO_THROW(list.remove(7, 0));
    EXPECT_NO_THROW(list.remove(9, 0));

    //Check priority values
    EXPECT_THROW(list.getPriorityVal(3), std::out_of_range);
    EXPECT_EQ(list.getPriorityVal(0), "2a");
    EXPECT_EQ(list.getPriorityVal(1), "4a");
    EXPECT_EQ(list.getPriorityVal(2), "8a");
    EXPECT_EQ(list.numPriorityItems(), 3);

    //Check all normal values
    EXPECT_THROW(list.getNormalVal(0, 0), std::out_of_range);
    EXPECT_EQ(list.getNormalVal(1, 0), "1a");
    EXPECT_EQ(list.getNormalVal(2, 0), "2a");
    EXPECT_EQ(list.getNormalVal(3, 0), "3a");
    EXPECT_EQ(list.getNormalVal(4, 0), "4a");
    EXPECT_THROW(list.getNormalVal(7, 0), std::out_of_range);
    EXPECT_EQ(list.getNormalVal(8, 0), "8a");
    EXPECT_THROW(list.getNormalVal(9, 0), std::out_of_range);
}
