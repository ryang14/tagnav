#include <map>
#include <vector>
#include <AceRoutine.h>
#include "navigation.h"

using namespace ace_routine;
using namespace std;

map<int, vector<int> > tags;
int currentTag = -1;
int destinationTag = -1;

// Link two tags together as adjacent
// Inputs: tag1 - first tag ID, tag2 second tag ID
// Returns: none
void link_tags(int tag1, int tag2)
{
    tags[tag1].push_back(tag2);
    tags[tag2].push_back(tag1);
}

// Get the distemce in tags from one tag to another
// Inputs: current - current tag ID, destination - destination tag ID
// Returns: the number of tags between current and destination
int distance_to_tag(int current, int destination)
{
    // Handle errors
    if(tags.find(current) == tags.end()) return -1;

    // Calculate distance
    int shortestDistance = INT8_MAX;
    if(destination == current) return 0;
    for(int tag : tags.find(current)->second)
    {
        // Destination tag is adjacent to the current tag
        if(tag == destination) return 1;

        // Find shortest distance to destination
        if(distance_to_tag(tag, destination) >= 0 && distance_to_tag(tag, destination) < shortestDistance)
        {
            shortestDistance = distance_to_tag(tag, destination);
        }
    }
    if(shortestDistance != INT8_MAX) return shortestDistance + 1;

    // Destination not found
    return -1;
}

// Get the distemce in tags from one tag to another
// Inputs: none
// Returns: the number of tags between current and destination
int distance_to_tag() { return distance_to_tag(currentTag, destinationTag); }

// Get the next tag towards destination
// Inputs: current - current tag ID, destination - destination tag ID
// Returns: the next tag to dive to
int next_tag(int current, int destination)
{
    // Handle errors
    if(currentTag < 0 && destinationTag < 0) return -1;
    if(tags.find(current) == tags.end()) return -1;

    // Find next tag
    int nextTag = -1;
    int shortestDistance = INT8_MAX;
    if(destination == current) return current;
    for(int tag : tags.find(current)->second)
    {
        // Destination tag is adjacent to the current tag
        if(tag == destination) return destination;
        // Find shortest path to destination
        if(distance_to_tag(tag, destination) >= 0 && distance_to_tag(tag, destination) < shortestDistance)
        {
            shortestDistance = distance_to_tag(tag, destination);
            nextTag = tag;
        }
    }

    return nextTag;
}

// Get the next tag towards destination
// Inputs: none
// Returns: the next tag to drive to
int next_tag()  
{
    return next_tag(currentTag, destinationTag);
}

// Navigate to a tag
// Inputs: destination - destination tag ID
// Returns: next tag ID to drive to
int navigate_to(int destination)
{
    destinationTag = destination;
    return next_tag();
}

// Sets the current tag
// Inputs: current - current tag ID
// Returns: none
void set_current_tag(int current)
{
    currentTag = current;
}

// Gets the current tag
// Inputs: none
// Returns: current tag ID
int get_current_tag()
{
    return currentTag;
}

// Gets the destination tag
// Inputs: none
// Returns: destination tag ID
int get_destination_tag()
{
    return destinationTag;
}

COROUTINE(navigation)
{
  COROUTINE_BEGIN();

  while (true)
  {
    COROUTINE_DELAY(1000);
  }
  
  COROUTINE_END();
}