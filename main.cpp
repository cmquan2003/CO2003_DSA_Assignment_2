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
void tcBasic() {
    ConcatStringTree sA("Hello"), sB(",_t"), sC("his_is"), sD("_an");
    cst s1(sA.concat(sB));
    cst s2(sC.concat(sD));
    cst s3(s1.concat(s2));
    cst s4 = s3.subString(1, 10);
    cst s5 = s4.reverse();
    cout << s1.length() << " " << s2.length() << " ";
    try {
        cout << s1.get(14);
    } catch (out_of_range &ofc) {
        cout << ofc.what() << " ";
    }
    cout << s2.get(1) << endl;
    cout << s1.indexOf('i') << " " << s2.indexOf('i') << endl;
    cout << s1.toStringPreOrder() << endl;
    cout << s5.toStringPreOrder() << endl;

    cout << s1.toString() << endl;
    cout << s2.toString() << endl;
    cout << s3.toString() << endl;
    // char a[9]; for (int i = 0; i < s4.length(); i++) a[i] = s4.get(i); for (int i = 0; i < s4.length(); i++) cout << s4.indexOf(a[i]) << " ";cout << endl;
    
    cout << s1.getParTreeSize("") << " ";
    cout << s3.getParTreeSize("ll") << endl; // == sA.getParTreeSize("")
    cout << s1.getParTreeStringPreOrder("") << endl;
    cout << s2.getParTreeStringPreOrder("") << endl;
    cout << s3.getParTreeStringPreOrder("") << endl;
}
void tcParentsTree() {
    ConcatStringTree sA("ABC"), sB("DEF"), sC("GHI");
    ConcatStringTree s1 = sA.concat(sB);
    ConcatStringTree s2 = sB.concat(sC);
    ConcatStringTree s3 = s1.concat(s2);
    cout << sA.getParTreeStringPreOrder("") << '\n'; // ParentsTree[(id=1);(id=4)]
    cout << sB.getParTreeStringPreOrder("") << '\n'; // ParentsTree[(id=4);(id=2);(id=5)]
    cout << sC.getParTreeStringPreOrder("") << '\n'; // ParentsTree[(id=3);(id=5)]
    cout << s1.getParTreeStringPreOrder("") << '\n'; // ParentsTree[(id=4);(id=6)]
    cout << s2.getParTreeStringPreOrder("") << '\n'; // ParentsTree[(id=5);(id=6)]
    cout << s3.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=6)]
    cout << endl;

    ConcatStringTree s4 = s1.concat(s3); // ABCDEFABCDEFDEFGHI
    ConcatStringTree s5 = s4.concat(s2); // ABCDEFABCDEFDEFGHIDEFGHI
    ConcatStringTree s6 = s3.concat(s5); // ABCDEFDEFGHIABCDEFABCDEFDEFGHIDEFGHI
    ConcatStringTree s7 = s1.concat(s2);
    cout << s6.toString() << " " << s6.length() << endl; // ConcatStringTree["ABCDEFDEFGHIABCDEFABCDEFDEFGHIDEFGHI"] 36
    cout << s1.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=6);(id=4);(id=7);(id=10)]
    cout << s2.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=6);(id=5);(id=8);(id=10)]
    cout << s3.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=7);(id=6);(id=9)]
    cout << s4.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=7);(id=8)]
    cout << s5.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=8);(id=9)]
    cout << s6.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=9)]
    cout << s7.getParTreeStringPreOrder("") << endl; // ParentsTree[(id=10)]
    cout << endl;

    cout << s6.getParTreeStringPreOrder("rlrl") << endl; // ParentsTree[(id=6);(id=4);(id=7);(id=10)]

    // Check delete in subString/reverse
    ConcatStringTree s8 = s3.subString(1, s3.length()-1); // ConcatStringTree["BCDEFDEFGH"]
    ConcatStringTree s9 = s3.reverse(); // ConcatStringTree["IHGFEDFEDCBA"]
    ConcatStringTree s10 = s8.concat(s9); // ConcatStringTree["BCDEFDEFGHIHGFEDFEDCBA"]
    cout << s10.toString() << endl;
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
void randomtc() {
    ConcatStringTree *s1 = new ConcatStringTree("he"), *s2 = new ConcatStringTree("t_"), *s5 = new ConcatStringTree("_lai_sang_thu");
    ConcatStringTree *s3 = new ConcatStringTree(s1->concat(*s2));
    ConcatStringTree *s4 = new ConcatStringTree(s3->concat(*s1));
    ConcatStringTree *s6 = new ConcatStringTree(s4->concat(*s5));
    cout << s4->toString() << endl;
    cout << s5->toString() << endl;
    cout << s6->toString() << endl;
    delete s5;
    delete s4;
    delete s2;
    delete s3;
    delete s6;
    delete s1;
}
int main() {
    // tc1();
    // cout << '\n';
    // tc2();
    // mytc();
    // tc3();
    tcParentsTree();
    // tcBasic();
    // randomtc();
    cout << "\nTesting Succeeded";
    return 0;
}
