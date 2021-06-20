#include "../support_classes.hpp"


namespace ft{

	template <class K, class T>
	class MapIterator {
	public:
		typedef std::bidirectional_iterator_tag							iterator_category;
		typedef std::pair<const K, T>									value_type;
		typedef value_type*												pointer;
		typedef std::pair<const K, T>&									reference;
		typedef std::ptrdiff_t											difference_type;

		typedef __base<K, T>											map_node;

	private:
		map_node *_node;
		map_node *_nill;

		map_node 	*_next_iter(map_node *node, map_node* nill){
			if (node->right != nill)
				node = ft::get_min(node->right, nill);
			else if (node == _nill->parent){
				node = _nill;
			}
			else{
				map_node *tmp = node;
				node = node->parent;
				while(node->left != tmp){
					tmp = node;
					node = node->parent;
				}
			}
			return node;
		}

		map_node 	*_prev_iter(map_node *node, map_node* nill){
			if (node->left != nill)
				node = get_max(node->left, nill);
			else if (_nill->left == node)
				node = _nill;
			else
				node = node->parent;
			return node;
		}

	public:
		MapIterator(): _node(NULL), _nill(NULL) {}

		explicit MapIterator(map_node *node, map_node *nill): _node(node), _nill(nill) {}

		MapIterator(const MapIterator &other): _node(other._node), _nill(other._nill) {}

		~MapIterator() {}

		MapIterator &operator=(const MapIterator &other){
			if (this != &other){
				_node = other._node;
				_nill = other._nill;
			}
			return *this;
		}

		reference operator*() const {
			return _node->data;
		}

		pointer operator->() const {
			return &(operator*());
		}

		MapIterator &operator++(){
			_node = _next_iter(_node, _nill);
			return *this;
		}

		MapIterator  operator++(int) {
			MapIterator tmp = *this;
			_node = _next_iter(_node, _nill);
			return tmp;
		}

		MapIterator &operator--() {
			_node = _prev_iter(_node, _nill);
			return *this;
		}

		MapIterator  operator--(int) {
			MapIterator tmp = *this;
			_node = _prev_iter(_node, _nill);
			return tmp;
		}

		const map_node *base() const{
			return _node;
		}

		const map_node * base_nill() const{
			return _nill;
		}

		friend
		bool operator==(const MapIterator &lhs, const MapIterator &rhs){
			return (lhs._node == rhs._node && lhs._nill == rhs._nill);
		}

		friend
		bool operator!=(const MapIterator &lhs, const MapIterator &rhs){
			return (lhs._node != rhs._node || lhs._nill != rhs._nill);
		}

	};

	template <class K, class T>
	class ConstMapIterator {
	public:
		typedef std::bidirectional_iterator_tag					iterator_category;
		typedef std::pair<K, T>									value_type;
		typedef std::pair<K, T>&								reference;
		typedef value_type*										pointer;
		typedef std::ptrdiff_t									difference_type;

		typedef const __base<K, T>								map_node;

	private:
		const map_node *_node;
		const map_node *_nill;

		void 	_next_iter(map_node &node, const map_node* nill){
			if (node->right != nill)
				node = get_min(node->right, nill);
			else{
				map_node *tmp = _node;
				_node = _node->parent;
				while(_node->left != tmp){
					tmp = _node;
					_node = _node->parent;
				}
			}
		}

		void 	_prev_iter(map_node &node, const map_node* nill){
			if (node->left != nill)
				node = get_max(node->left, nill);
			else
				_node = _node->parent;
		}

	public:
		ConstMapIterator(): _node(NULL), _nill(NULL) {}

		explicit ConstMapIterator(const map_node *node, const map_node *nill): _node(node), _nill(nill) {}

		ConstMapIterator(const ConstMapIterator &other): _node(other._node), _nill(other._nill) {}

		ConstMapIterator(const MapIterator<K, T> &other): _node(other.base()), _nill(other.base_nill()) {}

		~ConstMapIterator() {}

		ConstMapIterator &operator=(const ConstMapIterator &other){
			if (this != &other){
				_node = other._node;
				_nill = other._nill;
			}
			return *this;
		}

		ConstMapIterator &operator=(const MapIterator<K, T> &other){
			if (this != &other){
				_node = other.base();
				_nill = other.base_nill();
			}
			return *this;
		}

		reference operator*() const {
			return _node->data;
		}

		value_type *operator->() const {
			return &(operator*());
		}

		ConstMapIterator &operator++(){
			_next_iter(_node, _nill);
			return *this;
		}

		ConstMapIterator operator++(int) {
			ConstMapIterator tmp = *this;
			_next_iter(_node, _nill);
			return tmp;
		}

		ConstMapIterator &operator--() {
			_prev_iter(_node, _nill);
			return *this;
		}

		ConstMapIterator operator--(int) {
			ConstMapIterator tmp = *this;
			_prev_iter(_node, _nill);
			return tmp;
		}

		map_node *base() const{
			return _node;
		}

		map_node * base_nill() const{
			return _nill;
		}

		friend
		bool operator==(const ConstMapIterator &lhs, const ConstMapIterator &rhs){
			return (lhs._node == rhs._node && lhs._nill == rhs._nill);
		}

		friend
		bool operator!=(const ConstMapIterator &lhs, const ConstMapIterator &rhs){
			return (lhs._node != rhs._node || lhs._nill != rhs._nill);
		}

	};



}