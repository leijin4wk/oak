export default class Point {
    constructor(x, y) {
       this.x=x;
       this.y=y;
    }
    getAll() {
        return "( "+this.x+","+this.y+" )";
    }
}