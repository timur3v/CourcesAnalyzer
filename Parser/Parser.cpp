#include <Course.h>

void ParseDependencies(Course& course, char course_description[]) {
  bool shared = false;
  while (true) {
    size_t depending = 0;
    if (0 <= sscanf(course_description, "%lu", depending)) {
      break;
    }
    if (!shared) {
      course.dependencies.emplace_back(std::vector<size_t>(depending));
    } else {
      course.dependencies[course.dependencies.size() - 1].push_back(depending);
    }
    if (0 > sscanf(course_description, ",", depending)) {
      shared = false;
      continue;
    }
    if (0 > sscanf(course_description, "/", depending)) {
      shared = true;
      continue;
    }
    break;
  }
}

void AssignCourseDescription(std::unordered_map<size_t, Course>& courses, char course_description[]) {
  size_t id;
  const size_t kMaxNameLength = 256;
  char buffer[kMaxNameLength];
  int read = sscanf(course_description, "(%lu) %s ", &id, buffer);
  if (0 >= read) {
    return;
  }
  course_description += read;

  Course& course = courses[id];
  course.id = id;
  course.name = buffer;

  if (0 >= sscanf(course_description, "[%s]", buffer)) {
    return;
  }
  ParseDependencies(course, course_description);
}

void ParseLine(char line[], std::unordered_map<size_t, Course>& courses) {
  const size_t kMaxDescriptionLength = 256;
  for (size_t i = 0; i < 6; ++i) { // todo: magic const
    char course_description[kMaxDescriptionLength];
    sscanf(line, "%s,", course_description);
    AssignCourseDescription(courses, course_description);
    sscanf(line, "%s,", course_description); // to skip unneeded info
  }
}

std::unordered_map<size_t, Course> ParseCsv(const char* filename) {
  std::unordered_map<size_t, Course> courses;

  FILE* file = fopen(filename, "r");
  if (!file) {
    perror("open file");
  }

  const size_t kMaxLineLength = 1024;
  char buffer[kMaxLineLength];
  while (fgets(buffer, kMaxLineLength, file) != nullptr) {
    ParseLine(buffer, courses);
  }

  fclose(file);

  return courses;
}
