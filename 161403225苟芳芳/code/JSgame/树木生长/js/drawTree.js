/**
 *@author wbding
 *
 */


class Vector {
    constructor(x, y) {
        this.x = x || 0;
        this.y = y || 0;

    }

    add(v) {
        this.x += v.x;
        this.y += v.y;
        return this;

    }

    length() {
        return Math.sqrt(this.x * this.x + this.y * this.y);
    }

    rotate(angle) {
        this.x = Math.cos(angle) * this.x - Math.sin(angle) * this.y;
        this.y = Math.sin(angle) * this.x + Math.cos(angle) * this.y;
        return this;
    }
}

class Leaf {
    constructor(options = {}) {
        this.p = options.p || null;
        this.r = options.r || 0;
        this.c = options.c || 'rgba(255,255,255,1.0)';
        this.ctx = options.ctx;
    }

    render() {
        let r = Util.random(1, 4);
        for (let i = 0; i < 5; i++) {
            setTimeout(() => {
                Util.drawArc(this.ctx, this.p.x, this.p.y, r, this.c);
            }, i * 60);
        }

    }
}

//工具方法
class Util {
    static random(min, max) {
        return Math.random() * (max - min) + min;
    }

    static rgba(r, g, b, a) {
        return 'rgba(' + r + ',' + g + ',' + b + ',' + a + ')';
    }

    static randomrgba(min, max, a) {
        return this.rgba(Math.round(this.random(min, max)), Math.round(this.random(min, max)), Math.round(this.random(min, max)), a);

    }

    static drawArc(ctx, x, y, r, color) {
        ctx.beginPath();
        ctx.fillStyle = color;
        ctx.moveTo(x, y);
        ctx.arc(x, y, r, 0, 2 * Math.PI, true);
        ctx.fill();
    }
}

/***
 * 定义 Tree 类
 */
class Tree {
    constructor(obj = {}) {
        this.stat = {fork: 0, length: 0};
        this.branches = [];
        this.timer = null;
        this.start = true;
    }

    //添加分支
    addBranch(branch) {
        this.branches.push(branch);
        return this;
    }

    //移除分支
    removeBranch(branch) {
        this.branches.map((b, i) => {
            if (b === branch) {
                this.branches.splice(i, 1);
            }
        });
        return this;
    }

    //渲染
    render(cb = () => undefined) {
        let self = this;

        this.timer = setInterval(function () {
            if (self.start) {
                cb.call(self);
                let branches = self.branches;
                if (branches.length > 0) {
                    branches.map(b => {
                        b.grow();
                    })
                }
            }
        }, 1000 / 30);

    }

    //初始化
    init(ctx) {
        this.ctx = ctx;
    }

    //终止
    abort() {
        this.branches = [];
        this.stat.fork = 0;
        this.stat.length = 0;
    }

}

/**
 * 定义 树枝 Branch 类
 */
class Branch {
    constructor(options = {}) {
        //位置
        this.p = options.p || null;
        //矢量
        this.v = options.v || null;
        this.r = options.r || 0;
        this.tree = options.t || null;
        this.color = options.c || 'rgba(255,255,255,1.0)';
        this.length = 0;
        this.generation = 1;
        this.circle = 2 * Math.PI;
        this.register();
    }

    register() {
        this.tree.addBranch(this);
        return this;
    }

    draw() {
        let ctx = this.tree.ctx;
        ctx.beginPath();
        ctx.fillStyle = this.color;
        ctx.moveTo(this.p.x, this.p.y);
        ctx.arc(this.p.x, this.p.y, this.r, 0, this.circle, true);
        ctx.fill();
    }

    modify() {
        let angle = 0.18 - (0.10 / this.generation);
        this.p.add(this.v);
        this.length += this.v.length();
        this.r *= 0.99;
        this.v.rotate(Util.random(-angle, angle));
        if (this.r < 0.8 || this.generation > 10) {
            this.tree.removeBranch(this);
            //add leaf
            let l = new Leaf({
                p: this.p,
                c: this.color,
                ctx: this.tree.ctx
            });

            l.render();
        }
    }

    //分叉
    fork() {
        let p = this.length - Util.random(100, 200);
        if (p > 0) {
            let n = Math.round(Util.random(1, 3));
            this.tree.stat.fork += n - 1;
            for (let i = 0; i < n; i++) {
                this.clone(this);
            }
            this.tree.removeBranch(this);
        }
    }

    grow() {
        this.draw();
        this.modify();
        this.fork();
    }

    clone(b) {
        let r = new Branch(
            {
                p: new Vector(b.p.x, b.p.y),
                v: new Vector(b.v.x, b.v.y),
                r: b.r,
                c: b.color,
                t: b.tree
            });
        r.generation = b.generation + 1;
        return r;
    }

}


let drawInit = ($ele, options = {}) => {


    let html = ` <div id="drawArea" style="position: absolute">
            <canvas id="canvas" style="background-color: #000;cursor: pointer;"></canvas>
            <div class="operation" style="  position: absolute;
                left: 20px;
                top: 22px;
                border: 1px solid white;
                color:dodgerblue;
                padding: 0px 5px;">
            分叉数目:<span id="statmsg"></span>
             <span>(提示：点击页面不同区域可添加树)</span><br/>
            <button id="btnClear"  style="width: 100px;
            background-color: dodgerblue;
            margin: 5px auto;">清除页面</button>
             <button id="btnStop_Start"  style="width: 100px;
            background-color: dodgerblue;
            margin: 5px auto;">开始/暂停绘画</button>
         
              <button id="btnReload"  style="width: 100px;
            background-color: dodgerblue;
            margin: 5px auto;">重新开始</button>
           
        </div>`;
    $ele.append(html);
    let {width, height} = options;

    let center_x = width / 2,
        stretch = 600 / height,
        y_speed = 3 / stretch;
    let $statMsg = $("#statmsg");

    let $canvas = $('#canvas')[0];
    $canvas.width = width;
    $canvas.height = height;
    let ctx = $canvas.getContext('2d');
    ctx.globalCompositeOperation = "lighter";
    let tree = new Tree();
    tree.init(ctx);
    new Branch({
        p: new Vector(center_x, height),
        v: new Vector(Util.random(-1, 1), -y_speed),
        r: 15 / stretch,
        c: Util.randomrgba(0, 255, 0.3),
        t: tree
    });

    tree.render(function () {
        $statMsg.html(this.stat.fork);
    });

    $("#drawArea").click(function (e) {
        //e.preventDefault();
        let x, y;
        x = e.pageX - this.offsetLeft;
        y = e.pageY - this.offsetTop;
        new Branch({
            p: new Vector(x, height),
            v: new Vector(0, -y_speed),
            r: 15 / stretch,
            c: Util.randomrgba(0, 255, 0.3),
            t: tree
        });
    });

    $("#btnClear").click(function (e) {
        e.stopPropagation();
        tree.abort();
        ctx.clearRect(0, 0, width, height);
        $statMsg.html("0");

    });
    $("#btnStop_Start").click(function (e) {
        e.stopPropagation();
        tree.start =  !tree.start;
    })
    $("#btnReload").click(function (e) {
        e.stopPropagation();
        window.location.reload();
    });
};

class DrawTree {
    constructor(el, opt) {
        this.$ele = el;
        let $window = $(window);
        let [canvas_width, canvas_height] = [$window.width(), $window.height() - 30];
        this.defaults = {
            width: canvas_width,
            height: canvas_height
        };
        this.options = $.extend({}, this.defaults, opt);
    }

    init() {
        drawInit(this.$ele, this.options);
    }

}


;(function ($) {
    $.fn.drawTree = function (opt = {}) {
        let d = new DrawTree(this, opt);
        d.init();
    };
})(jQuery)