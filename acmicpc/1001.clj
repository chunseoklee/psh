(defn -main []
  (println (apply - (map #(Integer/parseInt %) (.split (read-line) " ")))))

(-main)