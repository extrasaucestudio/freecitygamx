void freecitygame::receive_nfttransfer(name from, name to, vector<uint64_t> asset_ids, string memo) {
   if(to == _self && memo.size() > 0){
      if(is_number(memo)){
         blend_nft(from, to_int<int32_t>(memo), asset_ids);
      }
      else if(memo == STAKE_MEMO){
         stake_nfts(from, asset_ids);
      }
   }
}