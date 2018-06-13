//Offline CHT
struct Line{
    ll m,c;
    Line(ll x,ll y){m=x; c=y;}
    ll Get(ll x) {return m*x+c;}
    bool operator<(const Line &other) const {return m < other.m;}
};

bool Bad(Line &P,Line &C,Line &N){
    return 1.0*(P.c-C.c)*(N.m-P.m) > 1.0*(P.c-N.c)*(C.m - P.m);
}

struct ConvexHull{
    vector<Line>hull;

    void Add(ll m,ll c){
        //For Max Query : Add(-m,-c)
        //For Min Query : Add(m,c)
        if(hull.size()>0 && hull.back().m==m) {
            if(hull.back().c<c) hull.pop_back();
            else return;
        }

        hull.push_back(Line(m, c));
        int sz=hull.size();
        while(sz>2 && Bad(hull[sz-3],hull[sz-2],hull[sz-1])){
            swap(hull[sz-2],hull[sz-1]); hull.pop_back(); sz--;
        }
    }

    ll Query(ll x) {
        int lo=-1;
        int hi=hull.size()-1;
        while(hi-lo>1) {
            int mid=(lo+hi)/2;
            if(hull[mid].Get(x)>=hull[mid+1].Get(x)) lo=mid;
            else hi=mid;
        }
        return hull[hi].Get(x);
        //For Max Query : return -hull[hi].Get(x);
    }
};