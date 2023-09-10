#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  //DNAstrand(Node& head);
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  //void PushBack(char to_add);

  //std::string ToString();
 
  //keep track of previous so that once match is found, the previous pointer can point to the new
  //location of the pattern you want to splice in
  //always have access to the next pointer and then just point the inserted pattern to the tail
  //make sure to get reference to next before deleting node so that you can delete the original memory
  //edge cases
  //literally head and tail
  //if head, then there is no previous node, so move around tail pointer that you're inserting
  //if tail, then instead of setting tail value to next, just set to nullptr

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr; 
  bool CheckMatch(const char* pattern, Node& start);
  int FindMatch(const char* pattern, int count); //second param int count
  void DeleteFromNode(Node& start, int count);
  
  //void SetHead(char to_add);
  //void SetTail(char to_add);


};



#endif
