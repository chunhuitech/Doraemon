用const修饰对指针指向的内容不能修改 如下，
ITreeModelData *insertChildren(int position, const ITreeModelDataItem * tmdi);
相关知识：
const修饰指针的情况，见下式：
int b = 500;
const int* a = &b          [1]
int const *a = &b          [2]
int* const a = &b          [3]
const int* const a = &b    [4]
参考《Effective c++》上的做法，
如果const位于星号的左侧，则const就是用来修饰指针所指向的变量，即指针指向为常量；
如果const位于星号的右侧，const就是修饰指针本身，即指针本身是常量。
因此，[1]和[2]的情况相同，都是指针所指向的内容为常量（const放在变量声明符的位置无关），这种情况下不允许对内容进行更改操作，如不能*a = 3；
[3]为指针本身是常量，而指针所指向的内容不是常量，这种情况下不能对指针本身进行更改操作，如a++是错误的；
[4]为指针本身和指向的内容均为常量。
