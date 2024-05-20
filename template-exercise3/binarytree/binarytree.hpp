
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
// #include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
// #include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public PreOrderTraversableContainer<Data>,
                   virtual public PostOrderTraversableContainer<Data>,
                   virtual public InOrderTraversableContainer<Data>,
                   virtual public BreadthTraversableContainer<Data> {  

private:

  // ...

protected:

  using Container::size; 

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node& var) const noexcept {
      return (Element() == var.Element());
    }; // Comparison of abstract types is possible, but should not be visible.
    
    bool operator!=(const Node& var) const noexcept {
      return !(operator==(var));
    }; // Comparison of abstract types is possible, but should not be visible.

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node& operator=(const Node& var) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    Node& operator=(Node&& var) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data& Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept{
      return ((!HasLeftChild()) && (!HasRightChild()));
    }; // (concrete function should not throw exceptions)

    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual const Node& LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

    virtual const Node& RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };
  /* ************************************************************************ */

  
  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree<Data>& operator=(const BinaryTree& var) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BinaryTree<Data>& operator=(BinaryTree&& var) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTree& var) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator!=(const BinaryTree& var) const noexcept {
    return !(operator==(var));
  };  // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node& Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

   using typename TraversableContainer<Data>::TraverseFun;

  virtual void Traverse(TraverseFun func) const override;  // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  virtual void PreOrderTraverse(TraverseFun func) const override;  // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  
  virtual void PostOrderTraverse(TraverseFun func) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  virtual void InOrderTraverse(TraverseFun func) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  virtual void BreadthTraverse(TraverseFun func) const override; // Override BreadthTraversableContainer member

protected:
 // Auxiliary member function (for PreOrderMappableContainer)

  void RecursivePreOrderTraverse(const Node *node, TraverseFun func) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)

  void RecursivePostOrderTraverse(const Node *node, TraverseFun func) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)

  void RecursiveInOrderTraverse(const Node *node, TraverseFun func) const; // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)

  void NotRecursiveBreadthTraverse(const Node *node, TraverseFun func) const; // Accessory function executing from one node of the tree

};


/* ************************************************************************** */

template <typename Data>
  class MutableBinaryTree : virtual public ClearableContainer,
                            virtual public BinaryTree<Data>,
                            virtual public PreOrderMappableContainer<Data>,
                            virtual public PostOrderMappableContainer<Data>,
                            virtual public InOrderMappableContainer<Data>,
                            virtual public BreadthMappableContainer<Data> {


private:

  // ...

protected:

  // ...

public:

  struct MutableNode : public virtual BinaryTree<Data>::Node{

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode& operator=(const MutableNode& var) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    MutableNode& operator=(MutableNode&& var) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ********************************************************************** */

    // Specific member functions

    using BinaryTree<Data>::Node::Element;
    virtual Data& Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

    using BinaryTree<Data>::Node::RightChild;
    using BinaryTree<Data>::Node::LeftChild;
    virtual  MutableNode& LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual  MutableNode& RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree<Data>& operator=(const MutableBinaryTree& var) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  MutableBinaryTree<Data>& operator=(MutableBinaryTree&& var) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Specific member functions
  using BinaryTree<Data>::Root;
  virtual  MutableNode& Root()  = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

   using typename MappableContainer<Data>::MapFun;

  virtual void inline Map(MapFun func) override {
    PreOrderMap(func);
  }; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  inline virtual void PreOrderMap(MapFun func) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  inline virtual void PostOrderMap(MapFun func) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  inline virtual void InOrderMap(MapFun func) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  inline virtual void BreadthMap(MapFun func) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary member function (for PreOrderMappableContainer)

  void RecursivePreOrderMap(MutableNode *node, MapFun func); // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for PostOrderMappableContainer)

  void RecursivePostOrderMap(MutableNode *node, MapFun func); // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for InOrderMappableContainer)

  void RecursiveInOrderMap(MutableNode *node, MapFun func); // Accessory function executing from one node of the tree

  /* ************************************************************************ */

  // Auxiliary member function (for BreadthMappableContainer)

  void NotRecursiveBreadthMap(MutableNode *node, MapFun func); // Accessory function executing from one node of the tree

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : public virtual ForwardIterator<Data>,
                           public virtual ResettableIterator<Data>{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node* root=nullptr;
  const typename BinaryTree<Data>::Node* current=nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stack;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data>& var); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator& var);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator&& var) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator& operator=(const BTPreOrderIterator& var);

  // Move assignment
  BTPreOrderIterator& operator=(BTPreOrderIterator&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPreOrderIterator& var) const noexcept;
  bool operator!=(const BTPreOrderIterator& var) const noexcept {
    return !(operator==(var));
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator : virtual public MutableIterator<Data>,
                                  virtual public BTPreOrderIterator<Data> {

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data>& var) : BTPreOrderIterator<Data>(var) {;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator<Data>& var) : BTPreOrderIterator<Data>(var) {;};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator<Data>&& var) noexcept : BTPreOrderIterator<Data>(std::move(var)) {;};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator& var);

  // Move assignment
  BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPreOrderMutableIterator& var) const noexcept {
    return BTPreOrderIterator<Data>::operator==(var);
  };
  inline bool operator!=(const BTPreOrderMutableIterator& var) const noexcept {
    return BTPreOrderIterator<Data>::operator!=(var);
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override {
  if(this->current!=nullptr) {
    return const_cast<Data&>((this->current)->Element());
  } else {
    throw std::out_of_range("Error: Out of range iterator"); 
  } 
}; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : public virtual ForwardIterator<Data>, 
                            public virtual ResettableIterator<Data>{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node* root=nullptr;
  const typename BinaryTree<Data>::Node* current=nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stack;

  const typename BinaryTree<Data>::Node* DeepestLeftLeaf(const typename BinaryTree<Data>::Node* actual);

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data>& var); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator& var);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator&& var) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator& operator=(const BTPostOrderIterator<Data>& var);

  // Move assignment
  BTPostOrderIterator& operator=(BTPostOrderIterator<Data>&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTPostOrderIterator& var) const noexcept;
  inline bool operator!=(const BTPostOrderIterator& var) const noexcept {
    return !(operator==(var));
  }

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : virtual public MutableIterator<Data>,
                                   virtual public BTPostOrderIterator<Data> {

private:

protected:

public:

  // Specific constructors
  BTPostOrderMutableIterator(MutableBinaryTree<Data>& var) : BTPostOrderIterator<Data>(var) {;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator& var) : BTPostOrderIterator<Data>(var) {;};

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator&& var) noexcept : BTPostOrderIterator<Data>(std::move(var)) {;};

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator& var);

  // Move assignment
  BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTPostOrderMutableIterator& var) const noexcept {
    return BTPostOrderIterator<Data>::operator==(var);
  };
  inline bool operator!=(const BTPostOrderMutableIterator& var) const noexcept {
    return !(operator==(var));
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override {
    if(this->current!=nullptr) {
      return const_cast<Data&>((this->current)->Element());
    } else {
      throw std::out_of_range("Out of range iterator"); 
    } 
  }; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : virtual public ForwardIterator<Data>,
                          virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* current=nullptr;
  const typename BinaryTree<Data>::Node* root=nullptr;
  StackVec<const typename BinaryTree<Data>::Node*> stack;

  const typename BinaryTree<Data>::Node* MostLeftNode(const typename BinaryTree<Data>::Node* );

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data>& var); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator& var);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator&& var) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator& operator=(const BTInOrderIterator& var);

  // Move assignment
  BTInOrderIterator& operator=(BTInOrderIterator&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTInOrderIterator& var) const noexcept;
  inline bool operator!=(const BTInOrderIterator& var) const noexcept {
    return !(operator==(var));
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator<Data>& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTInOrderIterator<Data> {

private:

protected:

public:

  // Specific constructors
  BTInOrderMutableIterator(MutableBinaryTree<Data>& var) : BTInOrderIterator<Data>(var) {;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator& var) : BTInOrderIterator<Data>(var) {;};

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator&& var) noexcept : BTInOrderIterator<Data>(std::move(var)) {;};

  /* ************************************************************************ */

  // Destructor
  virtual ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  inline BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator& var);

  // Move assignment
  inline BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTInOrderMutableIterator& var) const noexcept {
    return BTInOrderIterator<Data>::operator==(var);
  };
  inline bool operator!=(const BTInOrderMutableIterator& var) const noexcept {
    return !(operator==(var));
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override {
    if(this->current!=nullptr) {
      return const_cast<Data&>((this->current)->Element());
    } else {
      throw std::out_of_range("Out of range iterator"); 
    } 
  }; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */



template <typename Data>
class BTBreadthIterator : virtual public ForwardIterator<Data>, 
                          virtual public ResettableIterator<Data> {

private:

protected:

  const typename BinaryTree<Data>::Node* current=nullptr;
  const typename BinaryTree<Data>::Node* root=nullptr;
  QueueVec<const typename BinaryTree<Data>::Node*> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data>& var); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator& var);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator&& var) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator& operator=(const BTBreadthIterator& var);

  // Move assignment
  BTBreadthIterator& operator=(BTBreadthIterator&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BTBreadthIterator& var) const noexcept;
  inline bool operator!=(const BTBreadthIterator& var) const noexcept {
    return !(operator==(var));
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator& operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */


template <typename Data>
class BTBreadthMutableIterator : virtual public MutableIterator<Data>,
                                 virtual public BTBreadthIterator<Data> {

private:

protected:

public:

  // Specific constructors
  BTBreadthMutableIterator(MutableBinaryTree<Data>& var) : BTBreadthIterator<Data>(var) {;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator& var) : BTBreadthIterator<Data>(var) {;};

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator&& var) noexcept : BTBreadthIterator<Data>(std::move(var)) {;};

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator& var);

  // Move assignment
  BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&& var) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator==(const BTBreadthMutableIterator& var) const noexcept {
    return BTBreadthIterator<Data>::operator==(var);
  };
  inline bool operator!=(const BTBreadthMutableIterator& var) const noexcept {
    return !(operator==(var));
  };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data& operator*() override {
    if(this->current!=nullptr) {
      return const_cast<Data&>((this->current)->Element());
    } else {
      throw std::out_of_range("Out of range iterator"); 
    } 
  }; 

};

/* ************************************************************************** */

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
