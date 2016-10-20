#ifndef BTREE_H_
# define BTREE_H_

union u_btnode_data
  {
    int as_int;
    void *as_ptr;
  };

typedef union u_btnode_data t_btnode_data;

struct s_btnode
{
  t_btnode_data data;
  struct s_btnode *parent;
  struct s_btnode *left;
  struct s_btnode *right;
};

typedef struct s_btnode t_btnode;

t_btnode *
bt_make_node(t_btnode_data data, t_btnode *parent, t_btnode *left, t_btnode *right);

int
bt_count_children(t_btnode *root);

void
bt_set_left(t_btnode *parent, t_btnode_data child_data);

void
bt_set_right(t_btnode *parent, t_btnode_data child_data);

void
bt_set_children(t_btnode *parent, t_btnode_data left_data, t_btnode_data right_data);

/*
** Depth of node
** The depth of a node is the number of edges from the node
** to the tree's root node.
*/
int
bt_get_node_depth(t_btnode *node);

/*
** Height of node
** The height of a node is the number of edges on the longest
** downward path between that node and a leaf.
*/
int
bt_get_node_height(t_btnode *node);

/*
** Level of node
** The level of a node is defined by 1 + the number of connections
** between the node and the root.
*/
int
bt_get_node_level(t_btnode *node);

#endif
