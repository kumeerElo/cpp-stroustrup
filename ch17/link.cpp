#include "std_lib_facilities.h"
#include "link.h"

void Link::print()
{
	Link* n = this;

	while(n){
		cout << n->val() << endl;
		n = n->next();
	}
}

void Link::add(Link* god)
{	
	Link* n = this;

	while (n->next()){
		n = n->next();
	}
	n->set_next(god);
}

int Link::size()
{
	Link* n = this;
	int size = 0;
	while (n){
		size++;
		n = n->next();
	}
	return size;
}

Link* Link::insert(Link* god, int pos)
{
	Link* n = this;
	if (pos < 0 || pos > n->size())
		error ("insert: ", "unacceptable index");

	if (pos ==0){
		god->set_next(this);
		return god;
	}

	int count = 1;
	while (count < pos){
		n = n->next();
		count++;
	}
	Link* save = n->next();
	n->set_next(god);
	god->set_next(save);
	return this;
}

Link* Link::remove(int pos)
{
	if (pos > this->size()-1)
		error ("remove: ", "unacceptable index");

	Link* n = this;
	int prevInd = 0;

	if (pos ==0){
		Link* save = n->next();
		delete n;
		return save;
	}

	while (prevInd < pos-1){
		n = n->next();
		prevInd++;
	}

	Link* prevLink = n;
	Link* nextLink = NULL;
	if (pos < this->size()-1)
		nextLink=prevLink->next()->next();
	
	prevLink->set_next(nextLink);	
	return this;
}

int main(){
try{
	Link* indianGods = new Link("bramha", 0);
	Link* god2 = new Link("vishnu",0);	
	Link* god3 = new Link("mahesh",0);	
	Link* god4 = new Link("ram",0);
	Link* god5 = new Link("hanumaan",0);
	Link* god6 = new Link("krishna",0);

	indianGods->add(god2);
	indianGods->add(god3);
	indianGods->add(god4);
	indianGods->add(god5);
	//Link* addGods = indianGods->insert(god6, 4);
	//addGods->print();
	cout << "Orig list" << endl;
	indianGods->print();
	cout << "after removing " << endl;
	Link* removeGod = indianGods->remove(4);
	removeGod->print();

}//try

catch(exception& e){
	cerr << "exception happened: " << e.what() << endl;
}
catch(...){
	cerr << "unknow exception happened: " << endl;
}

}//main
