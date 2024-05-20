#include "binarytreelnk.hpp"

namespace lasd
{

    /* ************************************************************************** */


    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> &var)
    {
        size = var.Size();
        QueueVec<NodeLnk **> queue;
        queue.Enqueue(&root);
        var.Traverse(
            [&queue](const Data &dat)
            {
                NodeLnk *&current = *queue.HeadNDequeue();
                current = new NodeLnk(dat);
                queue.Enqueue(&current->LChild);
                queue.Enqueue(&current->RChild);
            });
    }
    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> &&var) noexcept
    {
        size = var.Size();
        QueueVec<NodeLnk **> queue;
        queue.Enqueue(&root);
        var.Map(
            [&queue](const Data &dat)
            {
                NodeLnk *&current = *queue.HeadNDequeue();
                current = new NodeLnk(std::move(dat));
                queue.Enqueue(&current->LChild);
                queue.Enqueue(&current->RChild);
            });
    }

    /* ************************************************************************** */



    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk &var)
    {
        if(var.root!=nullptr) {
            root = new NodeLnk(*var.root);
            size = var.Size();
        }     
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk &&var) noexcept
    {
        std::swap(root, var.root);
        std::swap(size, var.size);
    }

    /* ************************************************************************** */


    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk &var)
    {
        Clear();
        if(var.root!=nullptr) {
            root = new NodeLnk(*var.root);
            size = var.Size();
        }    
        return *this;
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(BinaryTreeLnk &&var) noexcept
    {
        std::swap(root, var.root);
        std::swap(size, var.size);
        return *this;
    }

    template <typename Data>
    inline BinaryTreeLnk<Data>::NodeLnk::~NodeLnk()
    {
        if (LChild != nullptr)
        {
            delete LChild;
            LChild = nullptr;
        }
        if (RChild != nullptr)
        {
            delete RChild;
            RChild = nullptr;
        }
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk &var)
    {
        element = var.element;
        LChild = (var.LChild != nullptr) ? new NodeLnk(*var.LChild) : nullptr;
        RChild = (var.RChild != nullptr) ? new NodeLnk(*var.RChild) : nullptr;
    }

  template <typename Data>
  BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk &&var) noexcept
  {
      std::swap(element, var.element);
      std::swap(LChild, var.LChild);
      std::swap(RChild, var.RChild);
  }


    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk &var)
    {
        element(var->element);
        return *this;
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk &&var) noexcept
    {
        std::swap(element, var->element);
        return *this;
    }

    /* ************************************************************************** */

}
