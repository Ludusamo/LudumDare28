#include "PathFinder.h"

std::vector<Node> PathFinder::blacklist = std::vector<Node>();

PathFinder::PathFinder() {

}

//bool PathFinder::in_blacklist(uint32_t x, uint32_t y) {
//    for(int i = 0; i < PathFinder::blacklist.size(); i++)
//        if(x == PathFinder::blacklist[i].x && y == PathFinder::blacklist[i].y)
//            return true;
//    return false;
//}

bool PathFinder::in_blacklist(uint32_t x, uint32_t y) {
    for(int i = 0; i < PathFinder::blacklist.size(); i++)
        if(x == PathFinder::blacklist[i].x && y == PathFinder::blacklist[i].y)
            return true;
    return false;
}

std::vector<Node> PathFinder::pathfind(uint32_t srcy, uint32_t srcx, uint32_t tary, uint32_t tarx, std::vector<std::vector<int16_t> > level) {
    for(uint32_t x = 0; x < level.size(); x++)
        for(uint32_t y = 0; y < level[0].size(); y++)
            level[x][y] = level[x][y] == -8 ? 1 : 0;
    level[tary][tarx] = 1;
    for(int i = 0; i < level.size(); i++) {
       for(int j = 0; j < level[0].size(); j++) {
            std::cout << level[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::vector<Node> path;
    path.push_back(Node(srcx, srcy));
    if(srcx == tarx && srcy == tary)
        return path;
    std::string priority;
    uint32_t x = srcx, y = srcy;
    while(x != tarx || y != tary) {
        if(tarx > x && tary >= y)
            priority = "rdul";
        else if(tarx == x && tary > y)
            priority = "dlru";
        else if(tarx < x && tary <= y)
            priority = "ldur";
        else if(tarx == x && tary < y)
            priority = "ulrd";
        for(int i = 0; i < 4; i++) {
            switch(priority[i]) {
                case 'l':
                    if(path[path.size() -1].left && x != 1 && level[x - 1][y] == 1 && !in_blacklist(x-1,y)) {
                        x--;
                        path[path.size() - 1].left = false;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'u':
                    if(path[path.size() -1].up && y != 1 && level[x][y - 1] == 1 && !in_blacklist(x,y-1)) {
                        path[path.size() - 1].up = false;
                        y--;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'r':
                    if(path[path.size() -1].right && x != level.size() - 2 && level[x+1][y] == 1 && !in_blacklist(x+1,y)) {
                        path[path.size() - 1].right = false;
                        x++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'd':
                    if(path[path.size() -1].down && y != level[0].size() - 2 && level[x][y+1] == 1 && !in_blacklist(x,y+1)) {
                        path[path.size() - 1].down = false;
                        y++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
            }
            if(i == 3) {
                path.pop_back();
                x = path[path.size() - 1].x;
                y = path[path.size() - 1].y;
            }
        }
        BREAK:
        continue;
    }
    blacklist.clear();
    for(int i = 0; i < path.size(); i++)
        path[i].reverse();
    return path;
}

/***std::vector<Node> PathFinder::pathfind(uint32_t srcy, uint32_t srcx, uint32_t tarx, uint32_t tary, std::vector<std::vector<int16_t> > level, int16_t can_pass) {
    std::cout << srcx << " " << srcy << " to " << tarx << " " << tary << std::endl;
    for(uint32_t x = 0; x < level.size(); x++)
        for(uint32_t y = 0; y < level[0].size(); y++)
            level[x][y] = level[x][y] != can_pass ? 0 : 1;
    for(int i = 0; i < level.size(); i++) {
       for(int j = 0; j < level[0].size(); j++) {
            std::cout << level[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    level[srcx][srcy] = 1;
    level[tary][tarx] = 1;
    for(int i = 0; i < level.size(); i++) {
       for(int j = 0; j < level[0].size(); j++) {
            std::cout << level[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::vector<Node> path = std::vector<Node>();
    path.push_back(Node(srcx,srcy));
    if(srcx == tary && srcy == tarx)
        return path;
    uint32_t x = srcx, y = srcy;
    while(x != tary || y != tarx) {
        if(tarx > x && tary > y)
            priority = "rdul";
        else if(tarx == x && tary > y)
            priority = "dlru";
        else if (tarx > x && tary == y)
            priority = "rudl";
        else if(tarx < x && tary < y)
            priority = "ldur";
        else if(tarx == x && tary < y)
            priority = "ulrd";
        else if(tarx < x && tary == y)
            priority = "ludr";
        else if(tarx < srcx && tary > srcx)
            priority = "ldur";
        else if(tarx > srcx && tary < srcy)
            priority = "rudl";

        for(int i = 0; i < 4; i++) {
            //std::cout << priority << std::endl;
            switch(priority[i]) {
                case 'l':
                    if(path[path.size() -1].left && x != 1 && level[x - 1][y] == 1 && !in_blacklist(x-1,y)) {
                        std::cout << "Left" << std::endl;
                        path[path.size() - 1].left = false;
                        x--;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'u':
                    if(path[path.size() -1].up && y != 1 && level[x][y - 1] == 1 && !in_blacklist(x,y-1)) {
                        std::cout << "Up" << std::endl;
                        path[path.size() - 1].up = false;
                        y--;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'r':
                    if(path[path.size() -1].right && x != level.size() - 2 && level[x+1][y] == 1 && !in_blacklist(x+1,y)) {
                        std::cout << "Right" << std::endl;
                        path[path.size() - 1].right = false;
                        x++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'd':
                    if(path[path.size() -1].down && y != level[0].size() - 2 && level[x][y+1] == 1 && !in_blacklist(x,y+1)) {
                        std::cout << "Down" << std::endl;
                        path[path.size() - 1].down = false;
                        y++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
            }
            if(i == 3 && path.size() > 1) {
                path.pop_back();
                x = path[path.size() - 1].x;
                y = path[path.size() - 1].y;
            }
        }
        BREAK:
        continue;
    }
    blacklist.clear();
    for(int i = 0; i < path.size(); i++)
        path[i].reverse();
    return path;
}***/

/***std::vector<Node> PathFinder::pathfind(uint32_t srcy, uint32_t srcx, uint32_t tary, uint32_t tarx, std::vector<std::vector<int16_t> > level, int16_t can_pass) {
    for(uint32_t x = 0; x < level.size(); x++)
        for(uint32_t y = 0; y < level[0].size(); y++)
            level[x][y] = level[x][y] != can_pass ? 0 : 1;
    std::cout << srcx << " " << srcy << std::endl;
    level[srcy][srcx] = 1;
    level[tary][tarx] = 1;
    for(int i = 0; i < level.size(); i++) {
       for(int j = 0; j < level[0].size(); j++) {
            std::cout << level[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::vector<Node> path = std::vector<Node>();
    path.push_back(Node(srcx,srcy));
    blacklist.push_back(Node(srcx,srcy));
    if(srcx == tary && srcy == tarx)
        return path;
    uint32_t x = srcx, y = srcy;
    /**while(x != tary || y != tarx) {
        if(tarx > x && tary > y)
            priority = "rdul";
        else if(tarx == x && tary > y)
            priority = "dlru";
        else if (tarx > x && tary == y)
            priority = "rudl";
        else if(tarx < x && tary < y)
            priority = "ludr";
        else if(tarx == x && tary < y)
            priority = "ulrd";
        else if(tarx < x && tary == y)
            priority = "ludr";
        else if(tarx < x && tary > y)
            priority = "ldur";
        else if(tarx > x && tary < y)
            priority = "rdul";
        std::cout << priority << std::endl;
        std::cout << srcx << " " << srcy << " to " << tarx << " " << tary << std::endl;
        for(uint32_t i = 0; i < 4; i++) {
            std::cout << priority << std::endl;
            switch(priority[i]) {
                case 'l':
                    if(path[path.size() -1].left && x != 1 && level[x - 1][y] == 1 && !in_blacklist(x-1,y)) {
                        std::cout << "Left" << std::endl;
                        path[path.size() - 1].left = 0;
                        x--;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'u':
                    if(path[path.size() -1].up && y != 1 && level[x][y - 1] == 1 && !in_blacklist(x,y-1)) {
                        std::cout << "Up" << std::endl;
                        path[path.size() - 1].up = false;
                        y--;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'r':
                    if(path[path.size() -1].right && x != level.size() - 2 && level[x+1][y] == 1 && !in_blacklist(x+1,y)) {
                        std::cout << "Right" << std::endl;
                        path[path.size() - 1].right = false;
                        x++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
                case 'd':
                    if(path[path.size() -1].down && y != level[0].size() - 2 && level[x][y+1] == 1 && !in_blacklist(x,y+1)) {
                        std::cout << "Down" << std::endl;
                        path[path.size() - 1].down = false;
                        y++;
                        path.push_back(Node(x,y));
                        blacklist.push_back(Node(x,y));
                        goto BREAK;
                    }
            }
            if(i == 3 && path.size() > 1) {
                path.pop_back();
                x = path[path.size() - 1].x;
                y = path[path.size() - 1].y;
            }
        }
        BREAK:
        break;
    }
    blacklist.clear();
    std::cout << path.size() << std::endl;
    return path;

}**/
