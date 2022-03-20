ACTION freecitygame::setblendcfg(int32_t template_id, string name, vector<int32_t> require_template_ids){
   require_auth(_self);
   check(require_template_ids.size() > 1, ERR_REQUIRE_TEMPLATE_IDS);
   sort(require_template_ids.begin(), require_template_ids.end());
   auto itr = blendconfigs.find((uint64_t)template_id);
   if(itr == blendconfigs.end()){
      blendconfigs.emplace(_self, [&](auto& _item) {
         _item.template_id = template_id;
         _item.name = name;
         _item.require_template_ids   = require_template_ids;
      });
   }
   else{
      blendconfigs.modify(itr, _self, [&](auto& _item) {
         _item.name = name;
         _item.require_template_ids   = require_template_ids;
      });
   }
}

ACTION freecitygame::rmblendcfg(int32_t template_id){
   require_auth(_self);
   auto itr = blendconfigs.require_find((uint64_t)template_id, ERR_BLEND_CONFIG_NOT_FOUND);
   blendconfigs.erase(itr);
}