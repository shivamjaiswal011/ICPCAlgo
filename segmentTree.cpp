
///segment tree  for minimum element


///Built function

void built(int *a, int *tree,int s,int e,int index)
{
	//Base case out of range
	if(s>e)return;
    //Base case leaf node
    if(s==e)
    {
    	tree[index]=a[s];
    	return;
    }

     ///recurcive call
    int mid=s+(e-s)/2
    //left part
    built(a,tree,s,mid,2*index);
    //right part
    built(a,tree,mid+1,e,(2*index)+1);
   
    //update according to question for finding minimum we use this
    tree[index]=min(tree[2*index],tree[2*index +1]);

     

}

//query function return according to ques 
int query(int *tree,int qs,int qe,int s,int e,int index)
{
	///no overlap  return acc to ques
	if(qs>e||qe<s)return INT_MAX;

	//complete overlap
	if(qs<=s && e<=qe )
       return tree[index];

   /// partial overlap
   int mid=s+(e-s)/2;
   query(tree,qs,qe,s,mid,2*index);
   query(tree,qs,qe,mid+1,e,2*index+1);
   //update acc to ques 
   return min(tree[2*index],tree[2*index+1]);
}

//update a single node 
void update (int *tree,int s,int e,int index,int val,int node)
{
	//out of range
	if(node>e||node<s)return;
	
	//leaf node
		if(s==e)
		{
			tree[index]=val;
			return;
		}

    //in range 
		int mid=s+(e-s)/2;
    update(tree,s,mid,2*index,val,node);		
	update(tree,mid+1,e,2*index+1,val,node);

	//update acc to ques 
	tree[index]=min(tree[2*index],tree[2*index+1]);
	return;
}


/// update with range increment all  with lazy propagation//
//we take another array of same length as that of tree
void updatelazy(int *tree,int *lazy,int s,int e,int index,int val,int rs,int re)
{
	  /// out of range 
	if(s>e)return;

	/// check for previous updates
	if(lazy[index]!=0)
	{
		tree[index]+=lazy[index];
		if(s!=e)//we are not on leaf node
		{
			lazy[2*index]+=lazy[index];
			lazy[2*index+1]+=lazy[index];
		}
		lazy[index]=0;
	}

	///if our tree node is up to date
	//then 3 conditions
	//no overlap with range
	if(rs>e||re<s)return;

	//complete overlap
	if(rs<=s&&re>=e)
	{
		tree[index]+=val;
		if(s!=e)//not leaf node
		{
           lazy[2*index]+=val;          
           lazy[2*index+1]+=val;
		}
		return;
	}

	//partial overlap
	int mid=s+(e-s)/2;
    updatelazy(tree,lazy,s,mid,2*index,val,rs,re);
    updatelazy(tree,lazy,mid+1,e,2*index+1,val,rs,re);
    tree[index]=min(tree[2*index],tree[2*index+1]);

}
