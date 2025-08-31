
{{- define "cosmoverse.name" -}}cosmoverse{{- end -}}
{{- define "cosmoverse.fullname" -}}cosmoverse{{- end -}}
{{- define "cosmoverse.labels" -}}{{- toYaml (dict "app.kubernetes.io/name" "cosmoverse" "app.kubernetes.io/part-of" "cosmoverse") -}}{{- end -}}
{{- define "cosmoverse.selectorLabels" -}}{{- toYaml (dict "app.kubernetes.io/name" "cosmoverse") -}}{{- end -}}
