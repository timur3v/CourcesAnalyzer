struct Course {
  size_t id;
  std::string name;
  std::vector<std::vector<size_t>> dependencies;
};
