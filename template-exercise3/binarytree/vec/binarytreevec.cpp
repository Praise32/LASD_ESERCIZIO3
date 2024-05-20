#include "binarytreevec.hpp"

namespace lasd {

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &dat, int i, BinaryTreeVec<Data>* bt) {
    this->bt = bt;
    this->index = i;
    bt->elem[i] = dat;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& dat, int i, BinaryTreeVec<Data>* bt) {
    std::swap(this->bt, bt);
    std::swap(this->index, i);
    std::swap(bt->elem[i], dat);
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
{
    if(static_cast<ulong>(index * 2 + 1) < bt->size) {
        return true;
    }
    return false;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
    if(static_cast<ulong>(index * 2 + 2)< bt->size) {
            return true;
    }
    return false;
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
    if(HasLeftChild()) {
        return (bt->Nodes[index*2+1]);
    }
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::LeftChild(): Not found!");
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const {
    if(HasRightChild()) {
        return (bt->Nodes[index*2+2]);
    }
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::RightChild(): Not found!");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() {
    if(HasLeftChild()) {
        return (bt->Nodes[index*2+1]);
    }
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::LeftChild(): Not found!");
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() {
    if(HasRightChild()) {
        return (bt->Nodes[index*2+2]);
    }
    else throw std::out_of_range("BinaryTreeVec<Data>::NodeVec::RightChild(): Not found!");
}

/* ************************************************************************** */

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data>& var) {
    this->Resize(var.Size());
    Nodes = new NodeVec[var.Size()];
    int i = 0;
    var.Traverse(
        [this, &i](const Data& dat){
            this->Nodes[i].index = i;
            elem[i] = dat;
            this->Nodes[i].bt = this;
            i++;
        }
    );
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> &&var) noexcept {
    this->Resize(var.Size());
    Nodes = new NodeVec[var.Size()];
    int i = 0;
    var.Map(
        [this, &i](Data& dat){
            this->Nodes[i].index = i;
            elem[i] = std::move(dat);
            this->Nodes[i].bt = this;
            i++;
        }
    );
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &var) {
    this->Resize(var.Size());
    Nodes = new NodeVec[var.Size()];
    std::copy(var.elem, var.elem + size, elem);
    std::copy(var.Nodes, var.Nodes + size, Nodes);
    for(lasd::ulong i = 0; i < var.Size(); i++) {
        Nodes[i].bt = this;
    }
}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> &&var) noexcept {
    std::swap(this->size, var.size);
    std::swap(elem, var.elem);
    std::swap(Nodes, var.Nodes);
    for(lasd::ulong i = 0; i < size; i++) {
        Nodes[i].bt = this;
    }
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& var) {
    this->Clear();
    this->Resize(var.Size());
    Nodes = new NodeVec[var.Size()];
    std::copy(var.elem, var.elem + size, elem);
    std::copy(var.Nodes, var.Nodes + size, Nodes);
    for(lasd::ulong i = 0; i < var.Size(); i++) {
        Nodes[i].bt = this;
    }
    return *this;
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec &&var) noexcept {
    std::swap(this->size, var.size);
    std::swap(elem, var.elem);
    std::swap(Nodes, var.Nodes);
    for(lasd::ulong i = 0; i < size; i++) {
        Nodes[i].bt = this;
    }
    for(lasd::ulong i = 0; i < var.size; i++) {
        var.Nodes[i].bt = &var;
    }
    return *this;
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const {
    if(!this->Empty()) {
        return Nodes[0];
    }
    else {
        throw std::length_error("BinaryTreeVec<Data>::Root(): Empty tree");
    }
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() {
    if(!this->Empty()) {
        return Nodes[0];
    }
    else {
        throw std::length_error("BinaryTreeVec<Data>::Root(): Empty tree");
    }
}

/* ************************************************************************** */

}