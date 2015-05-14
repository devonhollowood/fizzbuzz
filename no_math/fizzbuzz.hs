makeCycle :: (Int, String) -> [String]
makeCycle sound = cycle $ replicate (fst sound - 1) "" ++ [snd sound]

makeSounds :: [(Int, String)] -> [String]
makeSounds = zipWith choose count . foldr1 (zipWith (++)) . map makeCycle
    where count = map show [1..]
          choose a b = if null b then a else b

main = mapM_ putStrLn . take 100 $ makeSounds [(3, "Fizz"), (5, "Buzz")]
