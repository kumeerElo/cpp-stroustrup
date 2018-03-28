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

Link* Link::insert(Link* l, int pos)
{
	if (pos < 0 || pos > this->size())
		error ("Link::insert ", "unacceptable index");

	if (pos == 0){
		l->set_next(this);
		return l;
	}

	Link* prevLink = this;
	Link* currLink = prevLink->next();
	int curr = 1;

	while (curr < pos){
		prevLink = currLink;
		currLink = currLink->next();
		curr++;
	}

	prevLink->set_next(l);
	l->set_next(currLink);

	return this;	
}

Link* Link::remove(int pos)
{
	if (pos < 0 || pos >= this->size())
		error ("Link::remove: ", "wrong subscript");

	Link* prevLink = this;
	Link* currLink = prevLink->next();

	if (pos ==0){
		Link* nextLink = this->next();
		delete this;	
		return nextLink;
	}

	int count = 1;

	while (count < pos){
		prevLink = currLink;
		currLink = currLink->next();
		count++;
	}

	prevLink->set_next(currLink->next());
	delete currLink;
	return this;
}

Link* Link::find(string name)
{
	Link* n = this;
	if (n == NULL)
		error ("Link::find", "passed a null pointer");

	while(n){
		if (n->val() == name)
			return n;
		if (!n->next()){
			cout << "The element is not found\n";
			return NULL;
		}
		n = n->next();
	}
}

Link* Link::find_and_delete(string name)
{
	Link* save = this;
	Link* prevLink = this;
	Link* currLink = prevLink->next();

	if (!currLink){
		if (currLink->val() == name){
			delete currLink;
			return NULL;
		}
		return save;
	}

	if (prevLink->val()==name){
		Link* node = prevLink;
		prevLink = currLink;
		currLink = currLink->next();
		save = prevLink;
		delete node;	
	}

	while (currLink){
		if (currLink->val()==name){
			prevLink->set_next(currLink->next());

			Link* node = currLink;
			currLink = currLink->next();
			delete node;
			continue;
		}
		prevLink = currLink; 
		currLink = currLink->next();
	}
	return save;
}

int main(){
try{
	Link* indianGods = new Link("bramha", 0);
	Link* god2 = new Link("vishnu",0);	
	Link* god3 = new Link("mahesh",0);
	Link* god4 = new Link("ram",0);
	Link* god5 = new Link("hanumaan",0);

	// add
	indianGods->add(god2);
	indianGods->add(god3);
	indianGods->add(god4);
	indianGods->add(god5);

	/* find
	Link* god = indianGods->find("hanuman");
	if (god)
		cout <<  "found: " << god->val() << endl;
	*/

	/* find and delete 
	cout << "===orig list===" << endl;
	indianGods->print();

	Link* god6 = new Link("hanumaan",0);
	Link* modifiedList = indianGods->insert(god6,0);
	
	cout << "==modified list==" << endl;
	modifiedList->print();

	Link* removeElem = modifiedList->find_and_delete("hanumaan");

	cout << "==after deleting==" << endl;
	removeElem->print();
	*/

	/* insert 
	Link* god6 = new Link("krishna",0);
	Link* addGods = indianGods->insert(god6, 4);
	addGods->print();
	*/

	/* remove
	cout << "Orig list" << endl;
	indianGods->print();
	cout << "after removing " << endl;
	Link* removeGod = indianGods->remove(4);
	removeGod->print();
	*/

}//try

catch(exception& e){
	cerr << "exception happened: " << e.what() << endl;
}
catch(...){
	cerr << "unknow exception happened: " << endl;
}

}//main
