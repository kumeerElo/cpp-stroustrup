class Link
{
public:
	Link ():m_val(""), m_next(0){};
	Link(string val, Link* next=0) 
		:m_val(val),m_next(next){};

	Link* next(){return m_next;}
	string val(){return m_val;}
	void set_next(Link* n){m_next = n;}
	void set_value(string val){m_val = val;}

	void add(Link* god);
	void print();
	Link* insert(Link* god, int pos);
	int size();
	Link* remove(int pos);
	Link* find(string name);
	Link* find_and_delete(string name);
private:
	Link* m_next;
	string m_val;
};
