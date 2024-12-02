#include <iostream>
#include <vector>

using namespace std;

void find_lucky_numbers(vector<int> &nums,int step) {
    if (step > nums.size())
        return;

    vector<int> filtered_nums;
    for (int i = 0; i < nums.size(); i++) {
        if ((i + 1) % step != 0)
            filtered_nums.push_back(nums[i]);
    }

    nums = filtered_nums;
    find_lucky_numbers(nums, step + 1);

}

int main() {
    vector<int> nums;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        nums.push_back(i + 1);
    find_lucky_numbers(nums,2);
    for(int i=0;i<nums.size();i++)
        cout<<nums[i]<<" ";
    return 0;
}