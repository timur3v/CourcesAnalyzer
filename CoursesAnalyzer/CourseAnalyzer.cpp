#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <Course.h>

std::vector<std::unordered_set<size_t>> GetCoursesTrees(size_t root_course_id, std::unordered_map<size_t, Course>& courses) {
  std::vector<std::unordered_set<size_t>> possible_trees;
  for (std::vector<size_t>& dependency : courses[root_course_id].dependencies) {
    for (size_t i = 0; i < dependency.size(); ++i) {
      std::vector<std::unordered_set<size_t>> sub_trees = GetCoursesTrees(dependency[i], courses);
      for (auto& sub_tree : sub_trees) {
        sub_tree.insert(dependency[i]);
        possible_trees.emplace_back(std::move(sub_tree));
      }
    }
  }
  return possible_trees;
}

size_t GetSubjCount(std::unordered_set<size_t>& tree_courses) {
  std::vector<std::vector<size_t>> subjects_by_level;
  return 1;
}

void GetBestCourseSet(ToClose& to_close, std::unordered_map<size_t, Course>& courses) {
  auto trees_5 = GetCoursesTrees(to_close.level_5, courses);
  std::vector<std::vector<std::unordered_set<size_t>>> trees_3(3);
  for (size_t i = 0; i < trees_3.size(); ++i) {
    trees_3[i] = GetCoursesTrees(to_close.level_3[i], courses);
  }

  size_t min_subjects = -1;

  for (size_t i = 0; i < trees_5.size(); ++i) { // todo: simplify
    for (size_t j = 0; j < trees_3[0].size(); ++j) {
      for (size_t k = 0; k < trees_3[1].size(); ++k) {
        for (size_t l = 0; l < trees_3[2].size(); ++l) {
          std::unordered_set<size_t> tree_courses;
          tree_courses.merge(trees_5[i]);
          tree_courses.merge(trees_3[0][j]);
          tree_courses.merge(trees_3[1][k]);
          tree_courses.merge(trees_3[2][l]);
          if (tree_courses.size() < min_subjects) {
            min_subjects = std::min(min_subjects, GetSubjCount(tree_courses));
          }
        }
      }
    }
  }
}

