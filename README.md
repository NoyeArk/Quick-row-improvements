# Quick-row-improvements
## 简介
该项目是大二学习数据结构的课程设计：快速排序算法改进
## 功能实现
任务：快速排序法事应用最广泛的排序算法之一，最佳情况下时间复杂度是 O(nlogn)。但是最坏情况下可能达到O(n^2)。说明快速排序达到最坏情况的原因。  
1、选取随机数作为枢轴   
2、使用左端，右端和中心的中值做枢轴（三数取中法）   
3、每次选取数据集中的中位数做枢轴  
4、判断如果该区间内的元素值小于n（可以取5~15，视情况而定）的时候直接采取插入排序来处理该区间内的数据，从而提高效率  
要求：实现上述算法，并完成测试，输出每一步的变化过程。  

## 程序概述
![image](https://github.com/NoyeArk/Quick-row-improvements/assets/112805800/3c74e005-d215-41bf-8507-beec7f135347)
![image](https://github.com/NoyeArk/Quick-row-improvements/assets/112805800/a56ca20c-c0d2-44b4-803c-f420341d402c)

## 效果展示
![image](https://github.com/NoyeArk/Quick-row-improvements/assets/112805800/b557a782-fd7a-41b1-bd82-465601715b17)
