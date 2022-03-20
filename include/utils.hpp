namespace utils {
    /**
     * Check if a value exists in specific array
     */
    template<typename T>
    bool is_exists(std::vector<T> v, T K)
    {
        auto it = find(v.begin(), v.end(), K);
        return it != v.end();
    }

    /**
     * Get nft attribute value 
     */
    template <typename T>
    T get_nft_attribute_value(ATTRIBUTE_MAP data, std::string attribute) {
        T    result;
        auto attr = data.find(attribute);
        if (attr != data.end()) {
            std::visit(
                [&](ATOMIC_ATTRIBUTE&& arg) {
                    if (std::holds_alternative<T>(arg)) {
                        result = std::get<T>(arg);
                    }
                }, attr->second);
        }

        return result;
    }

    time_point_sec current_time_point_sec() {
        return time_point_sec(current_time_point());
    }

    /**
   * Split string with specific delimiter to array of string
   */
   std::vector<std::string> split(std::string s, std::string delimiter){
      vector<std::string> result = vector<std::string> {};

      size_t pos = 0;
      std::string token;
      while ((pos = s.find(delimiter)) != std::string::npos) {
         token = s.substr(0, pos);
         result.push_back(token);
         s.erase(0, pos + delimiter.length());
      }
      if(result.size() > 0){
         result.push_back(s);
      }

      return result;
   }

   /**
   * Convert string to int
   */
   template<typename T>
   T to_int(std::string value){
      
      T result = 0;
      if (!value.empty()) {
         result = std::strtoull(value.c_str(),NULL,0);
      }

      return result;
   }

   /*
   * Check if string is number
   */
   bool is_number(const std::string& s)
   {
      return !s.empty() && std::find_if(s.begin(), 
         s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
   }
}