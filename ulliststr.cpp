#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

  /**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::push_back(const std::string& val)
{
	//if list is empty
	if(empty())
	{
		//allocate a new item
		Item* newp = new Item;
		head_ = newp;
		tail_ = newp;
		newp->val[newp->first] = val;
		newp->last = 1;
		size_++;
	}

	//else if last one is occupied 
	else if((!empty()) && (tail_->last == ARRSIZE))
	{
		//allocate a new item
		Item* newp = new Item;
		newp->val[newp->first] = val;
		newp->last = 1;
		tail_->next = newp;
		newp->prev = tail_;
		newp->next = NULL;
		tail_ = newp;
		size_++;
	}

	//else (regular push back)
	else
	{
		tail_->val[tail_->last] = val;
		tail_->last++;
		size_++;
	}
}

  /**
   * Removes a value from the back of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_back()
{
	if(empty())
	return;

	if(size_ == 1)
	{
		delete tail_;
		tail_ = NULL;
		head_ = NULL;
		size_--;
	}
	else if((tail_->first) == (ARRSIZE-1))
	{
		Item* oldp = tail_;
		tail_ = oldp->prev;
		delete oldp;
		tail_->prev = NULL;
		size_--;
	}
	else
	{
		tail_->last--;
		size_--;
	}
}
  
  /**
   * Adds a new value to the front of the list.
   * If there is room before the 'first' value in
   * the head node add it there, otherwise, 
   * allocate a new head node.
   *   - MUST RUN in O(1)
   */
void ULListStr::push_front(const std::string& val)
{
	if(empty())
	{
		Item* newp = new Item;
		head_ = newp;
		tail_ = newp;
		newp->last = ARRSIZE;
		newp->val[ARRSIZE-1] = val;
		newp->first = ARRSIZE-1;
		size_++;
	}
	else if((!empty()) && (head_->first == 0))
	{
		Item* newp = new Item;
		newp->val[ARRSIZE-1] = val;//error
		newp->last = ARRSIZE;
		newp->first = ARRSIZE-1;
		head_->prev = newp;
		newp->next = head_;
		head_->prev = NULL;
		head_ = newp;
		size_++;
	}
	else
	{
		head_->val[head_->first - 1] = val;
		head_->first--;
		size_++;
	}
}

  /**
   * Removes a value from the front of the list
   *   - MUST RUN in O(1)
   */
void ULListStr::pop_front()
{
	if(empty())
	return;

	if(size_ == 1)
	{
		delete tail_;
		tail_ = NULL;
		head_ = NULL;
		size_--;
	}
	else if((head_->first) == (ARRSIZE-1))
	{
		Item* oldp = head_;
		head_ = oldp->next;
		delete oldp;
		head_->prev = NULL;
		size_--;
	}
	else
	{
		head_->first++;
		size_--;
	}
}

  /**
   * Returns a const reference to the back element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::back() const
{
	return tail_->val[tail_->last-1];
}

  /**
   * Returns a const reference to the front element
   *   - MUST RUN in O(1)
   */
std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

  /** 
   * Returns a pointer to the item at index, loc,
   *  if loc is valid and NULL otherwise
   *   - MUST RUN in O(n) 
   */
std::string* ULListStr::getValAtLoc(size_t loc) const
{
	Item* newp = head_;
	if(empty() || (loc>size_))
		return NULL;
	
	while((newp->last - newp->first) <= loc)
	{
		loc = loc - (newp->last - newp->first);
		newp = newp->next;
	}
	return &newp->val[loc + newp->first];
}
  

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
