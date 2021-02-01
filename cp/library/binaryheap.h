typedef long long ll;

//max heap
class binaryheap{
    public:
        vector<ll> heap;

        binaryheap(vector<ll> h){
            heap = h;
            buildheap();
        }

        void topdownheapify(ll i){
            //change name for min heap
            ll largest = i;
            ll left = 2*i +1;
            ll right = 2*i + 2;
            ll n = heap.size();

            //change for min heap
            if(left < n && heap[largest] < heap[left])
                largest = left;
            if(right < n && heap[largest] < heap[right])
                largest = right;
            if(largest != i){
                swap(heap[largest], heap[i]);
                topdownheapify(largest);
            }
        }

        void bottomupheapify(ll i){
            ll parent = (i+1)/2 - 1;
            while(parent > -1){
            //change for min heap
                if(heap[parent] < heap[i]){
                    swap(heap[parent], heap[i]);
                    i = parent;
                    parent = (i+1)/2 - 1;
                }
                else{
                    parent = -1;
                }
            }
        }

        void buildheap(){
            ll startindex = heap.size()/2 - 1;
            for(int i = startindex; i > -1; i--)
                topdownheapify(i);
        }

        ll pop(){
            swap(heap[0], heap[heap.size()-1]);
            ll ret = heap.back();
            heap.pop_back();
            topdownheapify(0);
            return ret;
        }

        ll top(){
            return heap[0];
        }

        void addKey(ll val){
            heap.push_back(val);
            bottomupheapify(heap.size()-1);
        }

        void changeKey(ll i, ll val){
            //change for min heap in this function
            int operation = heap[i] > val ? 1 : 0;

            //decrease operation
            if(operation == 1){
                heap[i] = val;
                topdownheapify(i);
            }
            //increase operation
            else{
                heap[i] = val;
                bottomupheapify(i);
            }

        }


};