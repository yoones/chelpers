#include <stdlib.h>
#include "xfunctions.h"
#include "btree.h"

t_btnode *
bt_make_node(t_btnode_data data, t_btnode *parent, t_btnode *left, t_btnode *right)
{
  t_btnode *node;

  node = xmalloc(sizeof(t_btnode));
  node->data = data;
  node->parent = parent;
  node->left = left;
  node->right = right;
  return (node);
}

int
bt_count_children(t_btnode *root)
{
  return (
	  (root->left == NULL ? 0 : 1 + bt_count_children(root->left))
	  +
	  (root->right == NULL ? 0 : 1 + bt_count_children(root->right))
	  );
}

void
bt_set_left(t_btnode *parent, t_btnode_data child_data)
{
  parent->left = bt_make_node(child_data, parent, NULL, NULL);
}

void
bt_set_right(t_btnode *parent, t_btnode_data child_data)
{
  parent->right = bt_make_node(child_data, parent, NULL, NULL);
}

void
bt_set_children(t_btnode *parent, t_btnode_data left_data, t_btnode_data right_data)
{
  bt_set_left(parent, left_data);
  bt_set_right(parent, right_data);
}

int
bt_get_node_depth(t_btnode *node)
{
  int i;

  i = 0;
  while (node->parent != NULL)
    {
      i++;
      node = node->parent;
    }
  return (i);
}

int
bt_get_node_height(t_btnode *node)
{
  int left_heigth;
  int right_heigth;
  
  left_heigth = (node->left == NULL ? 0 : bt_get_node_height(node->left) + 1);
  right_heigth = (node->right == NULL ? 0 : bt_get_node_height(node->right) + 1);
  return ((left_heigth > right_heigth ? left_heigth : right_heigth) + 1);
}

int
bt_get_node_level(t_btnode *node)
{
  return (bt_get_node_depth(node) + 1);
}
