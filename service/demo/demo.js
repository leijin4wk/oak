import { testAdd } from 'libtest.so'

let r=testAdd(1, 0.5,function (v){
    console.log("aaaa:",v)
})
console.log("r="+r)
let a=2;
let b=3;
console.log("a+b="+(a+b));
console.log(111);
console.log("quickjs");
console.log(new Date());
