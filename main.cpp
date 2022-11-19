#include "ConcatStringTree.h"

typedef ConcatStringTree cst;

void tc1() {
    ConcatStringTree s1("acbbcab");
    cout << s1.length() << endl;
    cout << s1.get(1) << endl;
    try {
        cout << "char at index 10: " << s1.get(10) << endl;
    }
    catch (const out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    cout << s1.indexOf('b') << endl;
}
void tc2() {
    ConcatStringTree s1("Hello");
    ConcatStringTree s2(",_t");
    ConcatStringTree s3 = s1.concat(s2);
    cout << s3.toStringPreOrder() << endl;
    cout << s3.toString() << endl;
    cout << s3.subString(5, 6).toString() << endl;
    cout << s3.reverse().toString() << endl;
}
void tc3() {
    ConcatStringTree * s1 = new ConcatStringTree("a");
    ConcatStringTree * s2 = new ConcatStringTree("b");
    ConcatStringTree * s3 = new ConcatStringTree(s1->concat(*s2));

    cout << s3->getParTreeSize("l") << endl;
    cout << s3->getParTreeStringPreOrder("l") << endl;

    delete s1;
    delete s2;
    delete s3;
}
void tc4() {
    // HashConfig hashConfig(
    //     2,
    //     0.5,
    //     0.5,
    //     0.75,
    //     2,
    //     4
    // );
    // LitStringHash * litStringHash = new LitStringHash(hashConfig);
    // ReducedConcatStringTree * s1 = new ReducedConcatStringTree("a", litStringHash);
    // ReducedConcatStringTree * s2 = new ReducedConcatStringTree("bb", litStringHash);

    // cout << s1->toString() << endl;
    // cout << s2->toString() << endl;
    // ReducedConcatStringTree * s3 = new ReducedConcatStringTree("bb", litStringHash);

    // cout << litStringHash->getLastInsertedIndex() << endl;
    // cout << litStringHash->toString() << endl;

    // delete litStringHash;
    // delete s3;
    // delete s1;
    // delete s2;
}
void tc5() {
    cst sA("Hello");
    cst sB(",_t");
    cst sC("his_is");
    cst sD("_an");
    cst s1(sA.concat(sB));
    cst s2(sC.concat(sD));
    cst s3(s1.concat(s2));
    cst s4 = s3.subString(1, 10);
    cst s5 = s4.reverse();
    // cout << sA.toString() << endl;
    // cout << sB.toString() << endl;
    // cout << sC.toString() << endl;
    // cout << sD.toString() << endl;
    // cout << s1.toString() << endl;
    // cout << s2.toString() << endl;
    // cout << s3.toString() << endl;
    cout << s4.toString() << endl;
    cout << s5.toString() << endl;
    // char a[9]; for (int i = 0; i < s4.length(); i++) a[i] = s4.get(i); for (int i = 0; i < s4.length(); i++) cout << s4.indexOf(a[i]) << " ";cout << endl;
    cout << s5.toStringPreOrder() << endl;
}
void randomtc() {
    ConcatStringTree sA("ABC"), sB("DEF"), sC("GHI");
    ConcatStringTree s1 = sA.concat(sB);
    ConcatStringTree s2 = sB.concat(sC);
    ConcatStringTree s3 = s1.concat(s2);
    ConcatStringTree s4 = s3.subString(1, s3.length()-1);
    ConcatStringTree s5 = s3.reverse();
    ConcatStringTree s6 = s1.concat(s3); // ABCDEFABCDEFDEFGHI
    ConcatStringTree s7 = s6.concat(s2); // ABCDEFABCDEFDEFGHIDEFGHI
    ConcatStringTree s8 = s3.concat(s7); // ABCDEFDEFGHIABCDEFABCDEFDEFGHIDEFGHI
    cout << s4.toString() << " " << s4.length() << endl; // ConcatStringTree["BCDEFDEFGH"] 10
    cout << s5.toString() << " " << s5.length() << endl; // ConcatStringTree["IHGFEDFEDCBA"] 12
    cout << s8.toString() << " " << s8.length() << endl; // ConcatStringTree["ABCDEFDEFGHIABCDEFABCDEFDEFGHIDEFGHI"] 36
    cout << s8.toStringPreOrder() << endl;
    // ConcatStringTree[(LL=12,L=36,<NULL>);(LL=6,L=12,<NULL>);(LL=3,L=6,<NULL>);(LL=0,L=3,"ABC");(LL=0,L=3,"DEF");(LL=3,L=6,<NULL>);(LL=0,L=3,"DEF");(LL=0,L=3,"GHI");(LL=18,L=24,<NULL>);(LL=6,L=18,<NULL>);(LL=3,L=6,<NULL>);(LL=0,L=3,"ABC");(LL=0,L=3,"DEF");(LL=6,L=12,<NULL>);(LL=3,L=6,<NULL>);(LL=0,L=3,"ABC");(LL=0,L=3,"DEF");(LL=3,L=6,<NULL>);(LL=0,L=3,"DEF");(LL=0,L=3,"GHI");(LL=3,L=6,<NULL>);(LL=0,L=3,"DEF");(LL=0,L=3,"GHI")]
    // (this answer may not be correct)
}
void mytc(){
    ConcatStringTree s1("this_is_");
    ConcatStringTree s2("my_basic_test");
    ConcatStringTree s3 = s1.concat(s2);
    cout<<"begin basic testcase 1"<<endl;
    cout<<"s1: "<<s1.toString()<<endl;
    cout<<"s2: "<<s2.toString()<<endl;
    cout<<"s3: "<<s3.toString()<<endl;
    cout<<"s1 length: "<<s1.length()<<endl;
    cout<<"s2 length: "<<s2.length()<<endl;
    cout<<"s3 length: "<<s3.length()<<endl;
    cout<<"in s1 'i' at index: "<< s1.indexOf('i')<<endl;
    cout<<"in s2 'a' at index: "<< s2.indexOf('a')<<endl;
    cout<<"in s3 'a' at index: "<< s3.indexOf('a')<<endl;
    cout<<"in s1 at index 4 is '"<<s1.get(4)<<"'"<<endl;
    cout<<"in s2 at index 6 is '"<<s2.get(6)<<"'"<<endl;
    cout<<"in s3 at index 10 is '"<<s3.get(10)<<"'"<<endl;
    cout<<" s1 preorder: "<<s1.toStringPreOrder()<<endl;
    cout<<" s2 preorder: "<<s2.toStringPreOrder()<<endl;
    cout<<" s3 preorder: "<<s3.toStringPreOrder()<<endl;
    cout<<"-----------"<<endl;
    ConcatStringTree abc("abc");
    ConcatStringTree def("def");
    ConcatStringTree ghi("ghi");
    ConcatStringTree jkl("jkl");
    ConcatStringTree abcdef = abc.concat(def);
    ConcatStringTree ghijkl = ghi.concat(jkl);
    ConcatStringTree abcdefghijkl = abcdef.concat(ghijkl);
    ConcatStringTree ab = abcdefghijkl.subString(0,2);
    ConcatStringTree kl = abcdefghijkl.subString(10,12);
    ConcatStringTree bcdefghi = abcdefghijkl.subString(1,9);
    cout<<"begin basic testcase 2"<<endl;
    cout<<abcdefghijkl.toString()<<endl;
    cout<<ab.toString()<<endl;
    cout<<kl.toString()<<endl;
    cout<<bcdefghi.toString()<<endl;
    cout<<"----"<<endl;
    cout<<abcdefghijkl.toStringPreOrder()<<endl;
    cout<<ab.toStringPreOrder()<<endl;
    cout<<kl.toStringPreOrder()<<endl;
    cout<<bcdefghi.toStringPreOrder()<<endl;
    cout<<"---------------"<<endl;
    ConcatStringTree ba = ab.reverse();
    ConcatStringTree lk = kl.reverse();
    ConcatStringTree ihgfedcb =bcdefghi.reverse();
    ConcatStringTree daivcl = abcdefghijkl.reverse();
    cout<<ba.toString()<<endl;
    cout<<lk.toString()<<endl;
    cout<<ihgfedcb.toString()<<endl;
    cout<<daivcl.toString()<<endl;
}
void tc7() {
    cst sA("abc");
    cst s1 = sA.concat(sA);
    cout << s1.toString() << endl;
    cout << s1.toStringPreOrder() << endl;
}
int main() {
    tc1();
    // cout << '\n';
    tc2();
    // mytc();
    // tc3();
    // randomtc();
    cout << "\nTesting Succeeded";
    return 0;
}
