(defun gps-line ()
  "Print the current buffer line number and narrowed line number of point."

  (interactive)
  (let ((start (point-min))
	(n (line-number-at-pos))
	(m (how-many "\n" (point-min) (point-max) nil)) )
    (if (= start 1)
	(message "Line %d/%d" n m)
      (save-excursion
	(save-restriction
	  (widen)
	  (message "line %d (narrowed line %d)"
		   (+ n (line-number-at-pos start) -1) n)))))




		   )
