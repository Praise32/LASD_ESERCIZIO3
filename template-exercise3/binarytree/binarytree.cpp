#include "binarytree.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
inline bool BinaryTree<Data>::operator==(const BinaryTree &var) const noexcept {
    if(size!=var.size) {
        return false;
    }
    BTPreOrderIterator i(*this);
    BTPreOrderIterator j(var);
    while(!(i.Terminated()) && !(j.Terminated())){
        if((*i)!=(*j)) {
            return false;
        }
        ++i; ++j;
    }
    return true;
}

template <typename Data>
void BinaryTree<Data>::Traverse(TraverseFun func) const {
    if(!this->Empty()) {
        PreOrderTraverse(
                [&func](const Data& dat) {
                    func(dat);
                }
            );
    }
}



template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun func) const {
  if(!(this->Empty())) {
    RecursivePreOrderTraverse(&this->Root(), func);
  }
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun func) const {
    if(!this->Empty()) {
        RecursivePostOrderTraverse(&this->Root(), func);
    }
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun func) const {
    if(!this->Empty()) {
        RecursiveInOrderTraverse(&this->Root(), func);
    }
}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun func) const{
    if(!this->Empty()) {
        NotRecursiveBreadthTraverse(&this->Root(), func);
    }
}

template <typename Data>
void BinaryTree<Data>::RecursivePreOrderTraverse(const Node* node, TraverseFun func) const {
    func(node->Element());    
    if(node->HasLeftChild()) {
        RecursivePreOrderTraverse(&node->LeftChild(), func);
    } 
    if(node->HasRightChild()) {
        RecursivePreOrderTraverse(&node->RightChild(), func);
    }      
}

template <typename Data>
void BinaryTree<Data>::RecursivePostOrderTraverse(const Node* node, TraverseFun func) const {
    if(node->HasLeftChild()) {
        RecursivePostOrderTraverse(&node->LeftChild(), func);
    }
    if(node->HasRightChild()) {
        RecursivePostOrderTraverse(&node->RightChild(), func);
    }
    func(node->Element());
}

template <typename Data>
void BinaryTree<Data>::RecursiveInOrderTraverse(const Node* node, TraverseFun func) const {
    if(node->HasLeftChild()) {
        RecursiveInOrderTraverse(&node->LeftChild(), func);
    }
    func(node->Element());
    if(node->HasRightChild()) {
        RecursiveInOrderTraverse(&node->RightChild(), func);
    }
}

template <typename Data>
void BinaryTree<Data>::NotRecursiveBreadthTraverse(const Node* node, TraverseFun func) const {
    lasd::QueueVec<const BinaryTree<Data>::Node *> queue;
    if(node!=nullptr) {
        queue.Enqueue(node);
    }

    while (!queue.Empty()) {
        const BinaryTree<Data>::Node *currentNode = queue.HeadNDequeue();
        func(currentNode->Element());

        if(currentNode->HasLeftChild()) {
            queue.Enqueue(&currentNode->LeftChild());
        }

        if(currentNode->HasRightChild()) {
            queue.Enqueue(&currentNode->RightChild());
        }
    }
}


template <typename Data>
inline void MutableBinaryTree<Data>::PreOrderMap(MapFun func)  {
    if(!(this->Empty())) {
        RecursivePreOrderMap(&this->Root(), func);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun func) {
    if(!(this->Empty())) {
        RecursivePostOrderMap(&this->Root(), func);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun func) {
    if(!(this->Empty())) {
       RecursiveInOrderMap(&this->Root(), func);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun func){
    if(!(this->Empty())) {
        NotRecursiveBreadthMap(&this->Root(), func);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::RecursivePreOrderMap(MutableNode* node, MapFun func){
    func(node->Element());
    if(node->HasLeftChild()) {
        RecursivePreOrderMap(&node->LeftChild(), func);
    }
    if(node->HasRightChild()) {
        RecursivePreOrderMap(&node->RightChild(), func);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::RecursivePostOrderMap(MutableNode* node, MapFun func){
    if(node->HasLeftChild()) {
        RecursivePostOrderMap(&node->LeftChild(), func);
    }
    if(node->HasRightChild()) {
        RecursivePostOrderMap(&node->RightChild(), func);
    }
    func(node->Element());
}

template <typename Data>
void MutableBinaryTree<Data>::RecursiveInOrderMap(MutableNode* node, MapFun func){
    if(node->HasLeftChild()) {
        RecursiveInOrderMap(&node->LeftChild(), func);
    }
    func(node->Element());
    if(node->HasRightChild()) {
        RecursiveInOrderMap(&node->RightChild(), func);
    }
}

template <typename Data>
void MutableBinaryTree<Data>::NotRecursiveBreadthMap(MutableNode* node, MapFun func){
    lasd::QueueVec<MutableBinaryTree<Data>::MutableNode *> queue;
    if(node!=nullptr) {
        queue.Enqueue(node);
    }

    while (!queue.Empty()) {
        MutableBinaryTree<Data>::MutableNode *currentNode = queue.HeadNDequeue();
        func(currentNode->Element());

        if(currentNode->HasLeftChild()) {
            queue.Enqueue(&currentNode->LeftChild());
        }

        if(currentNode->HasRightChild()) {
            queue.Enqueue(&currentNode->RightChild());
        }
    }
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& var) {
    if(!var.Empty()) {
        root = &var.Root();
        current = root;
    }
}


template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator &var) : stack(var.stack) {
    root = var.root;
    current = var.current;
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& var) noexcept : stack(std::move(var.stack)) {
    std::swap(root, var.root);
    std::swap(current, var.current);
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& var) {
    root = var.root;
    stack = var.stack;
    current = var.current;
    return *this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& var) noexcept {
    std::swap(root, var.root);
    std::swap(stack, var.stack);
    std::swap(current, var.current);
    return *this;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator &var) const noexcept {
    return (current==var.current && stack==var.stack);
}

template <typename Data>
const Data& BTPreOrderIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Iterator is terminated.");
    } else {
        return current->Element();
    }
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator++() {
    if(!Terminated()){
        if(current->HasLeftChild()){
            if(current->HasRightChild()) {
                stack.Push(&current->RightChild());
            }
            current=&(current->LeftChild());
        }else if(current->HasRightChild()) { 
            current=&(current->RightChild());
        } else if (!stack.Empty()) {
            current=stack.TopNPop();
        } else {
            current=nullptr;
        }
    } else {
        throw std::out_of_range("Out of range iterator");
    }
    return *this;
}

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
    stack.Clear();
    current = root;
}

/* ************************************************************************** */

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& var){
    if(var.Empty()) {
        root = nullptr;
    } else {
        root = &var.Root();
    }
    current = DeepestLeftLeaf(root);
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& var) {
    stack = var.stack;
    root = var.root;
    current=var.current;
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& var) noexcept : stack(std::move(var.stack)) {
    std::swap(root, var.root);
    std::swap(current, var.current);
}

template <typename Data>
const Data& BTPostOrderIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Iterator is terminated.");
    }
    else {
        return current->Element();
    }
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++(){
    if(!Terminated()){
        if(!(stack.Empty())){
            if (stack.Top()->HasRightChild() && !(&(stack.Top()->RightChild()) == current)) {
                current = &(stack.Top()->RightChild());
                current = DeepestLeftLeaf(current);
            } else {
                current = stack.TopNPop();
            }
        } else {
            current = nullptr;
        }
    }
    else {
        throw std::out_of_range("Iterator is terminated.");
    }

    return *this;
}

template <typename Data>
const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::DeepestLeftLeaf(const typename BinaryTree<Data>::Node* actual){
    if(actual!=nullptr){
        while(actual->HasLeftChild()){
            stack.Push(actual);
            actual = &(actual->LeftChild());
        }
        if(actual->HasRightChild()){
            stack.Push(actual);
            actual = &(actual->RightChild());
            actual = DeepestLeftLeaf(actual);
        }
    }
    return actual;
}


template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
    stack.Clear();
    current = DeepestLeftLeaf(root);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& var) {
    root=var.root;
    stack=var.stack;
    current=var.current;
    return *this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& var) noexcept {
    std::swap(root, var.root);
    std::swap(stack, var.stack);
    std::swap(current, var.current);
    return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator &var) const noexcept {
    return ((current == var.current) && (stack == var.stack));
}

/* ************************************************************************** */

template <typename Data>
const typename BinaryTree<Data>::Node *BTInOrderIterator<Data>::MostLeftNode(const typename BinaryTree<Data>::Node* actual) {
   while (actual != nullptr && (actual->HasLeftChild())) {
        stack.Push(actual);
        actual = &actual->LeftChild();
    }
    return actual;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &var) {
    if(var.Empty()) {
        root = nullptr;
    } else {
        root = &var.Root();
    }
    current = MostLeftNode(root);
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& var) {
    stack = var.stack;
    root = var.root;
    current=var.current;
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& var) noexcept : stack(std::move(var.stack)) {
    std::swap(current, var.current);
    std::swap(root, var.root);
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& var) {
    root = var.root;
    stack = var.stack;
    current = var.current;
    return *this;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& var) noexcept {
    std::swap(root, var.root);
    std::swap(stack, var.stack);
    std::swap(current, var.current);
    return *this;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator &var) const noexcept {
    return ((current == var.current) && (stack == var.stack));
}

template <typename Data>
const Data& BTInOrderIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Iterator is terminated.");
    } else {
        return current->Element();
    }
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept {
    return (current == nullptr);
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() {
    if(!Terminated()) {
        if((stack.Empty()) && !(current->HasRightChild())) {
            current=nullptr;
        }
        else { 
            if(current->HasRightChild()){
                current = MostLeftNode(&current->RightChild());
            } 
            else {
                current = stack.TopNPop();
            }
        }
    } else {
        throw std::out_of_range("Iterator is terminated.");
    }

    return *this;
}

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
    stack.Clear(); 
    current = MostLeftNode(root);
}

/* ************************************************************************** */

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& var) {
    if(var.Empty()) {
        root = nullptr;
    } else {
        root = &var.Root();
    }
    current = root;
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator &var) {
    queue = var.queue;
    root = current = var.current;
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& var) noexcept : queue(std::move(var.queue)) {
    std::swap(root, var.root);
    std::swap(current, var.current);
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& var) {
    root = var.root;
    queue = var.queue;
    current = var.current;
    return *this;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& var) noexcept {
    std::swap(root, var.root);
    std::swap(queue, var.queue);
    std::swap(current, var.current);
    return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator &var) const noexcept {
    return (current == var.current && queue == var.queue);
}

template <typename Data>
const Data& BTBreadthIterator<Data>::operator*() const {
    if(Terminated()) {
        throw std::out_of_range("Iterator is terminated.");
    } else {
        return current->Element();
    }
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept {
    return (current==nullptr);
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() {
    if(!Terminated()) {
        if (current != nullptr) {
            if (current->HasLeftChild()) queue.Enqueue(&(current->LeftChild())); 
            if (current->HasRightChild()) queue.Enqueue(&(current->RightChild()));
            
            if (!queue.Empty()) current = queue.HeadNDequeue();
            else current = nullptr;
        } 
    } else {
        throw std::out_of_range("Iterator is terminated.");
    }

    return *this;
}

template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
    queue.Clear();
    current = root;
}


/* ************************************************************************** */


template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(const BTPreOrderMutableIterator& var) {
    this->root=var.root;
    this->stack=var.stack;
    this->current=var.current;
    return *this;
}

template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator=(BTPreOrderMutableIterator&& var) noexcept {
    this->root = std::move(var.root);
    this->stack = std::move(var.stack);
    this->current = std::move(var.current);
    return *this;
}


template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(const BTPostOrderMutableIterator& var) {
    this->root=var.root;
    this->stack=var.stack;
    this->current=var.current;
    return *this;
}

template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator=(BTPostOrderMutableIterator&& var) noexcept {
    std::swap(this->root, var.root);
    std::swap(this->stack, var.stack);
    std::swap(this->current, var.current);
    return *this;
}

template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(const BTInOrderMutableIterator& var) {
    this->root=var.root;
    this->stack=var.stack;
    this->current=var.current;
    return *this;
}

template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator=(BTInOrderMutableIterator&& var) noexcept {
    std::swap(this->root, var.root);
    std::swap(this->stack, var.stack);
    std::swap(this->current, var.current);
    return *this;
}

template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(const BTBreadthMutableIterator& var) {
    this->root=var.root;
    this->queue=var.queue;
    this->current=var.current;
    return *this;
}

template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator=(BTBreadthMutableIterator&& var) noexcept {
    std::swap(this->root, var.root);
    std::swap(this->queue, var.queue);
    std::swap(this->current, var.current);
    return *this;
}


/* ************************************************************************** */
}
